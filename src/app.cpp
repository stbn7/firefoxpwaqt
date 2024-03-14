#include "app.h"

App::App()
{}

App::App(QString &iconPath, QString &name, QString &address, QString &id, QString description, QString &profile) :
    m_iconPath(iconPath),
    m_name(name),
    m_address(address),
    m_id(id),
    m_description(description),
    m_profile(profile)
{}

QString App::name() const
{
    return m_name;
}

void App::setName(const QString &name)
{
    m_name = name;
}
QString App::address() const
{
    return m_address;
}

void App::setAddress(const QString &address)
{
    m_address = address;
}

QString App::id() const
{
    return m_id;
}

void App::setId(const QString &id)
{
    m_id = id;
}

QString App::categories() const
{
    return m_categories;
}

void App::setCategories(const QString &categories)
{
    m_categories = categories;
}

QString App::description() const
{
    return m_description;
}

void App::setDescription(const QString &description)
{
    m_description = description;
}

QString App::icon()
{
    return m_iconPath;
}

void App::setIcon(QString iconPath)
{
    m_iconPath = iconPath;
}

QString App::profile() const
{
    return m_profile;
}

void App::setProfile(const QString &profile)
{
    m_profile = profile;
}

QString App::manifest() const
{
    return m_manifest;
}

void App::setManifest(const QString &manifest)
{
    m_manifest = manifest;
}
