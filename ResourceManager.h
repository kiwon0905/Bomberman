#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <memory>



template<class T>
class ResourceManager
{
protected:
	std::unordered_map<std::string, std::pair<int, std::unique_ptr<T>>> resourceMap;
	bool create(std::string name);  //should return true if the resource is first requested
	void destroy(std::string name);
public:
	ResourceManager(){};
	virtual ~ResourceManager(){};
};

template<class T>
bool ResourceManager<T>::create(std::string name)
{
	if(resourceMap.count(name)==0)
	{
		resourceMap[name].first=1;
		resourceMap[name].second.reset(new T());
		return true;
	}
	else 
		++resourceMap[name].first;
#ifdef _debug
	else if(resourceMap.count(name)>0)
		++resourceMap[name].first;
	else //Something wrong!!
		std::cerr<<"Something's wrong in creating. Ref count: "<<resourceMap[name].first<<"\n";
#endif
	return false;
}

template<class T>
void ResourceManager<T>::destroy(std::string name)
{
#ifdef _debug
	if(resourceMap.find(name)==resourceMap.end())
	{
		std::cerr<<"Requested to destroy non existing resource"; return;
	}
#endif
	//if there is only one reference
	if(resourceMap[name].first==1)
	{
		std::cout<<resourceMap[name].first;
		resourceMap.erase(name);
	}
	else
		--resourceMap[name].first;
#ifdef _debug
	//if there is more than one reference
	else if(resourceMap[name].first>1)
	{
		resourceMap[name].first--;//decrement the ref count
		//std::cout<<name<<" --\n";
	}
	else//Something's wrong!
		std::cerr<<"Something's wrong in destroying. Ref count: \n";
#endif
}
