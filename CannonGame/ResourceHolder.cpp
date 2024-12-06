#include "ResourceHolder.h"

// TODO:
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> ResourceHolder::m_textures{};
/*
template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(filename))
	{
		stdL::cout << "Load Error" << std::endl;
	}
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	// TODO: insert return statement here
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	// TODO: insert return statement here
}
*/

#if 1
sf::Texture& ResourceHolder::getTexture(std::string name)
{
	auto texture = m_textures.find(name);
	if (texture == m_textures.end())
	{
		loadTexture(name);
	}

	return *m_textures[name];
}

void ResourceHolder::loadTexture(std::string name)
{
	sf::Texture texture;

	if (!texture.loadFromFile("Resources/" + name))
	{
		std::cout << "Cannot load " << name << std::endl;
	}
	else
	{
		std::cout << "Texture was loaded" << name << std::endl;

	}

	m_textures.insert({ name, std::make_shared<sf::Texture>(texture)});
}

#endif