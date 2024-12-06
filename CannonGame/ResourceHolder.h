#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>



// FIXME: из-за глобальных ресурсов при закрытии игры вылетает исключение
// 
//template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	//void load(Identifier id, const std::string& filename);

	//Resource& get(Identifier id);
	//const Resource& get(Identifier id) const;

	static sf::Texture& getTexture(std::string name);



private:
	static void loadTexture(std::string name);

private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
	//std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;


};




