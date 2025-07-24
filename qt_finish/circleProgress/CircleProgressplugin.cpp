#include "CircleProgress.h"
#include "CircleProgressplugin.h"

#include <QtPlugin>

CircleProgressPlugin::CircleProgressPlugin(QObject *parent)
    : QObject(parent)
{
}

void CircleProgressPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CircleProgressPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CircleProgressPlugin::createWidget(QWidget *parent)
{
    return new CircleProgressBar(parent);
}

QString CircleProgressPlugin::name() const
{
    return QLatin1String("circleProgress");
}

QString CircleProgressPlugin::group() const
{
    return QLatin1String("");
}

QIcon CircleProgressPlugin::icon() const
{
    return QIcon();
}

QString CircleProgressPlugin::toolTip() const
{
    return QLatin1String("");
}

QString CircleProgressPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool CircleProgressPlugin::isContainer() const
{
    return false;
}

QString CircleProgressPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="circleProgress" name="circleProgress">
</widget>)");
}

QString CircleProgressPlugin::includeFile() const
{
    return QLatin1String("CircleProgress.h");
}
