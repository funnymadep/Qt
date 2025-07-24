#include "gaugeprogressbarplugin.h"
#include "gaugeprogressbar.h"

#include <QtPlugin>

GaugeProgressBarPlugin::GaugeProgressBarPlugin(QObject *parent)
    : QObject(parent)
{}

void GaugeProgressBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GaugeProgressBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GaugeProgressBarPlugin::createWidget(QWidget *parent)
{
    return new GaugeProgressBar(parent);
}

QString GaugeProgressBarPlugin::name() const
{
    return QLatin1String("GaugeProgressBar");
}

QString GaugeProgressBarPlugin::group() const
{
    return QLatin1String("");
}

QIcon GaugeProgressBarPlugin::icon() const
{
    return QIcon();
}

QString GaugeProgressBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GaugeProgressBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GaugeProgressBarPlugin::isContainer() const
{
    return false;
}

QString GaugeProgressBarPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="GaugeProgressBar" name="gaugeProgressBar">
</widget>)");
}

QString GaugeProgressBarPlugin::includeFile() const
{
    return QLatin1String("gaugeprogressbar.h");
}
