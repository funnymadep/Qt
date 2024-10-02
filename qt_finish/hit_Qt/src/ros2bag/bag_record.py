import time
import signal
import os
import shutil
import subprocess
from datetime import datetime, timedelta
import configparser

# 读取配置文件
config = configparser.ConfigParser()
config.read('del_config.cn')

# 从配置文件中获取路径、磁盘空间阈值、删除间隔时间等参数
dstDir = config.get('Settings', 'dstDir')
low_disk_space_threshold = config.getint('Settings', 'low_disk_space_threshold') * 1024 * 1024  # 转换为字节
delete_interval = config.getint('Settings', 'delete_interval') * 60  # 转换为秒
delete_cutoff_days = config.getint('Settings', 'delete_cutoff_days')  # 删除多少天前的目录

def get_disk_free_space(directory):
    """返回指定目录的可用磁盘空间"""
    total, used, free = shutil.disk_usage(directory)
    return free

def suspend_process(pid):
    os.kill(pid, signal.SIGSTOP)

def resume_process(pid):
    os.kill(pid, signal.SIGCONT)

def delete_old_rosbags(directory, current_time):
    # 根据配置文件的删除间隔设置，计算删除的截止时间
    cutoff_time = current_time - timedelta(days=delete_cutoff_days)
    record_file = os.path.join(directory, "record.txt")

    # 读取record.txt中的内容
    if os.path.exists(record_file):
        with open(record_file, 'r') as file:
            recorded_folders = [line.strip() for line in file.readlines()]
    else:
        recorded_folders = []

    # 获取所有文件夹的名称和创建时间
    folders = []
    for folder_name in os.listdir(directory):
        folder_path = os.path.join(directory, folder_name)
        if os.path.isdir(folder_path):
            try:
                folder_time = datetime.strptime(folder_name, '%Y_%m_%d-%H_%M_%S')
                folders.append((folder_path, folder_time))
            except (IndexError, ValueError):
                print(f"Skipped: {folder_name}")
    
    # 按时间排序文件夹
    folders.sort(key=lambda x: x[1])

    # 检查磁盘空间
    free_space = get_disk_free_space(directory)
    if free_space < low_disk_space_threshold:
        print(f"Low disk space: {free_space / (1024 * 1024):.2f} MB, deleting 2 oldest folders.")
        
        deleted_count = 0
        for folder_path, folder_time in folders:
            folder_name = os.path.basename(folder_path)
            if folder_name not in recorded_folders:  # 检查record.txt中是否存在
                shutil.rmtree(folder_path)
                deleted_count += 1
                print(f"Deleted due to low space: {folder_path}")
            else:
                print(f"Skipped deletion (found in record.txt): {folder_path}")
            
            if deleted_count >= 2:  # 只删除2个文件夹
                break

    # 删除超过设置的天数（delete_cutoff_days）的文件夹
    for folder_path, folder_time in folders:
        folder_name = os.path.basename(folder_path)
        if folder_time < cutoff_time:
            if folder_name not in recorded_folders:  # 检查record.txt中是否存在
                shutil.rmtree(folder_path)
                print(f"Deleted: {folder_path}")
            else:
                print(f"Skipped deletion (found in record.txt): {folder_path}")

def record_bag_with_intervals():
    # 获取当前时间，格式化成目录名
    folder_name = datetime.now().strftime('%Y_%m_%d-%H_%M_%S')
    output_directory = os.path.join(dstDir, folder_name)

    process = subprocess.Popen(
        ['ros2', 'bag', 'record', '-o', output_directory, 
         '--compression-mode', 'file',
         '--compression-format', 'zstd',
         '/livox/lidar_3GGDLCR00200131', '/livox/lidar_3GGDLCR00200171', 
         '/livox/lidar_3GGDLCR00200321', '/livox/lidar_3GGDLCR00200371'],
        stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    start_time = time.time()
    total_duration = 60  # 总时长1分钟

    while time.time() - start_time < total_duration:
        time.sleep(0)  # 运行0.2秒
        # suspend_process(process.pid)  # 暂停4秒
        # time.sleep(0)
        # resume_process(process.pid)  # 恢复

    process.terminate()
    process.stdout.close()
    process.stderr.close()

if __name__ == "__main__":
    last_delete_time = time.time()

    while True:
        current_time = datetime.now()
        
        # 检查是否达到删除操作的间隔时间
        if time.time() - last_delete_time > delete_interval:
            delete_old_rosbags(dstDir, current_time)  # 删除旧的rosbag文件夹
            last_delete_time = time.time()  # 记录上一次删除操作的时间

        record_bag_with_intervals()  # 录制1分钟
