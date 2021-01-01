#include "scene.hpp"

void Scene::addModel(Model* pModel ){
    model_array.push_back(pModel);
}

void Scene::addLight(Light* pLight){
    light_array.push_back(pLight);
}
