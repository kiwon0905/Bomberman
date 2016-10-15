#include "GameMap.h"
#include <iostream>
#include <fstream>
#include <map>
#include "block.h"
#include "GameWorld.h"
#include <cassert>

GameMap::GameMap()
{
	queryRect.width=51;
	queryRect.height=48;
}


GameMap::~GameMap()
{
}

void GameMap::loadBackground(std::ifstream & fin)
{
	std::string backgroundSprite;
	std::getline(fin, backgroundSprite);
	std::string backgroundMusic;
	std::getline(fin, backgroundMusic);
	bgm.load(backgroundMusic);
	std::cout<<"Backgroundsprite: "<<backgroundSprite<<std::endl;
	background.load(backgroundSprite);
		//Set the background in the center of the screen
	background().setOrigin(272, 224);
	background().setPosition(512, 344);
	background().setScale(1.5, 1.5);
	std::cout<<"Height: "<<background().getGlobalBounds().height<<std::endl;
	std::cout<<"Left: "<<background().getGlobalBounds().left<<std::endl;
	std::cout<<"Top: "<<background().getGlobalBounds().top<<std::endl;
	std::cout<<"Width: "<<background().getGlobalBounds().width<<std::endl;
}

void GameMap::readBlockInfo(std::ifstream & fin, std::map<int, std::pair<std::string, EntityType>> & mapInfo)
{
	std::string dummy;
	//Read block info "Permanent"
	fin>>dummy;
	int nPermanent;
	fin>>nPermanent;std::cout<<"Permanent: "<<nPermanent<<std::endl;
	for(int i=1; i<=nPermanent; ++i)
	{
		int key;
		fin>>key;
		std::string sprite;
		std::getline(fin, sprite);
		sprite.erase(sprite.begin());
		mapInfo.insert(std::make_pair(key, std::make_pair(sprite, EntityType::PERMANENT_BLOCK)));
	}
	//Read block info "SemiPermanent"
	fin>>dummy;
	int nSemiPermanent;
	fin>>nSemiPermanent;std::cout<<"SemiPermanent: "<<nSemiPermanent<<std::endl;
	for(int i=1; i<=nSemiPermanent; ++i)
	{
		int key;
		fin>>key;
		std::string sprite;
		std::getline(fin, sprite);
		sprite.erase(sprite.begin());
		mapInfo.insert(std::make_pair(key, std::make_pair(sprite, EntityType::SEMIPERMANENT_BLOCK)));
	}
		//insert empty key
		mapInfo.insert(std::make_pair(0, std::make_pair("", EntityType::NOTHING)));
}

void GameMap::loadBlocks(std::ifstream & fin, std::map<int, std::pair<std::string, EntityType>> & mapInfo, GameWorld * g)
{
	for(int y=0; y<14; ++y)
	{
		for(int x=0; x<16; ++x)
		{
			int key;
			fin>>key;
			tiles[y][x]=Tile(x, y);
			std::cout<<key<<" ";
			if(key==0)
				continue;
			else if(mapInfo[key].second==EntityType::PERMANENT_BLOCK)
			{
				g->createBlock(EntityType::PERMANENT_BLOCK, mapInfo[key].first, x, y);
			}
			else if(mapInfo[key].second==EntityType::SEMIPERMANENT_BLOCK)
			{
				g->createBlock(EntityType::SEMIPERMANENT_BLOCK, mapInfo[key].first, x, y);
			}
		}
		std::cout<<std::endl;
	}
}

void GameMap::load(std::string name, GameWorld * g)
{
	std::map<int, std::pair<std::string, EntityType>> mapInfo;
	
	std::string dummy;
	std::ifstream fin;
	fin.open(name);

	loadBackground(fin);
	readBlockInfo(fin, mapInfo);
	loadBlocks(fin, mapInfo, g);
	bgm().play();
	fin.close();
}

void GameMap::draw(sf::RenderWindow & w)
{
	w.draw(background());
}

void GameMap::onEnter(int x, int y, Entity * e) //called when an entity enters this tile
{
	tiles[y][x].onEnter(e);
}

void GameMap::onExit(int x, int y, Entity * e) //called when an entity exits this tile
{
	tiles[y][x].onExit(e);
}

bool GameMap::isPassable(int x, int y)
{
	return tiles[y][x].isPassable();
}

std::vector<Entity*>& GameMap::getAllEntitiesWithin(int x, int y, int r)
{
	assert(0<=x && x<16 && 0<=y && y<14 && 1<=r && r<=16);//assert that the location and radius is valid
	queryList.clear();
	//Entities on the east and on the same tile
	for(int i=x, count=-1; i<16&&count<r ; ++i, ++count)
		queryList.insert(queryList.end(), tiles[y][i].getEntities().begin(), tiles[y][i].getEntities().end());
	//West
	for(int i=x-1, count=0; i>=0&&count<r; --i, ++count)
		queryList.insert(queryList.end(), tiles[y][i].getEntities().begin(), tiles[y][i].getEntities().end());
	//North
	for(int i=y+1, count=0; i<14&&count<r; ++i, ++count)
		queryList.insert(queryList.end(), tiles[i][x].getEntities().begin(), tiles[i][x].getEntities().end());
	//South
	for(int i=y-1, count=0; i>=0&&count<r; --i, ++count)
		queryList.insert(queryList.end(), tiles[i][x].getEntities().begin(), tiles[i][x].getEntities().end());

	return queryList;
}

std::vector<sf::Vector2i>& GameMap::getAllPossibleTilesWithin(int x, int y, int r)
{
	assert(0<=x && x<16 && 0<=y && y<14 && 1<=r && r<=16);//assert that the location and radius is valid
	queryVec.clear();
	//Entities on the east and on the same tile
	for(int i=x+1, count=0; i<16&&count<r ; ++i, ++count)
	{
		queryVec.push_back(sf::Vector2i(i, y));
		if(!tiles[y][i].isEmpty())
			break;
	}
	//West
	for(int i=x-1, count=0; i>=0&&count<r; --i, ++count)
	{
		queryVec.push_back(sf::Vector2i(i, y));
		if(!tiles[y][i].isEmpty())	
			break;
	}
	//North
	for(int i=y+1, count=0; i<14&&count<r; ++i, ++count)
	{
		queryVec.push_back(sf::Vector2i(x, i));
		if(!tiles[i][x].isEmpty())
			break;
	}
	//South
	for(int i=y-1, count=0; i>=0&&count<r; --i, ++count)
	{
		queryVec.push_back(sf::Vector2i(x, i));
		if(!tiles[i][x].isEmpty())
			break;
	}

	return queryVec;
}

std::vector<Entity*>& GameMap::getEntitiesOn(int x, int y)
{
	queryList.clear();
	queryList.insert(queryList.end(), tiles[y][x].getEntities().begin(), tiles[y][x].getEntities().end());
	return queryList;
}

sf::FloatRect& GameMap::getBoundary(int x, int y)
{
	queryRect.top=8+y*48;
	queryRect.left=104+x*51;
	return queryRect;
}

void GameMap::bomb()
{

	
}

void GameMap::onExplosion(int x, int y, Explosion * e)
{
	tiles[y][x].onExplosion(e);
}
void GameMap::onExplosionExit(int x, int y, Explosion * e)
{
	tiles[y][x].onExplosionExit(e);
}

void GameMap::onItem(int x, int y, Item * i)
{
	tiles[y][x].onItem(i);
}

void GameMap::onItemExit(int x, int y, Item * i)
{
	tiles[y][x].onItemExit(i);
}