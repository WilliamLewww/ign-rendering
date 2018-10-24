/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#if defined(__APPLE__)
  #include <OpenGL/gl.h>
  #include <GLUT/glut.h>
#elif not defined(_WIN32)
  #include <GL/glew.h>
  #include <GL/gl.h>
  #include <GL/glut.h>
#endif

#include <iostream>
#include <vector>

#include <ignition/common/Console.hh>
#include <ignition/common/MeshManager.hh>
#include <ignition/rendering.hh>

#include "example_config.hh"
#include "GlutWindow.hh"

using namespace ignition;
using namespace rendering;


const std::string RESOURCE_PATH =
    common::joinPaths(std::string(PROJECT_BINARY_PATH), "media");


//////////////////////////////////////////////////
void buildScene(ScenePtr _scene)
{
  // initialize _scene
  _scene->SetAmbientLight(0.2, 0.2, 0.2);
  VisualPtr root = _scene->RootVisual();

  // create green material
  MaterialPtr green = _scene->CreateMaterial();
  green->SetDiffuse(0.0, 0.8, 0.0);
  green->SetSpecular(0.2, 0.4, 0.2);

  // create cylinder visual
  VisualPtr cylinder = _scene->CreateVisual("cylinder");
  cylinder->AddGeometry(_scene->CreateCylinder());
  cylinder->SetLocalPosition(3, 0.5, 0.5);
  cylinder->SetLocalScale(1, 1, 1);
  cylinder->SetMaterial(green);
  root->AddChild(cylinder);

  // create a mesh
  VisualPtr mesh = _scene->CreateVisual("duck");
  mesh->SetLocalPosition(3, -1, 0);
  mesh->SetLocalRotation(1.5708, 0, 2.0);
  MeshDescriptor descriptor;
  descriptor.meshName = common::joinPaths(RESOURCE_PATH, "duck.dae");
  common::MeshManager *meshManager = common::MeshManager::Instance();
  descriptor.mesh = meshManager->Load(descriptor.meshName);
  MeshPtr meshGeom = _scene->CreateMesh(descriptor);
  mesh->AddGeometry(meshGeom);
  root->AddChild(mesh);

  // create red material
  MaterialPtr red = _scene->CreateMaterial();
  red->SetDiffuse(0.8, 0.0, 0.0);
  red->SetSpecular(0.5, 0.2, 0.2);

  // create sphere visual
  VisualPtr sphere = _scene->CreateVisual("sphere");
  sphere->AddGeometry(_scene->CreateSphere());
  sphere->SetLocalPosition(2.5, 0, 0.3);
  sphere->SetLocalRotation(0, 0, 0);
  sphere->SetLocalScale(0.5, 0.5, 0.5);
  sphere->SetMaterial(red);
  root->AddChild(sphere);

  // create white material
  MaterialPtr white = _scene->CreateMaterial();
  white->SetDiffuse(0.8, 0.8, 0.8);
  white->SetSpecular(0.4, 0.4, 0.4);

  // create plane visual
  VisualPtr plane = _scene->CreateVisual("plane");
  plane->AddGeometry(_scene->CreatePlane());
  plane->SetLocalScale(5, 8, 1);
  plane->SetLocalPosition(3, 0, -0.5);
  plane->SetMaterial(white);
  root->AddChild(plane);

  // create directional light
  DirectionalLightPtr light0 = _scene->CreateDirectionalLight();
  light0->SetDirection(0.5, 0.5, -1);
  light0->SetDiffuseColor(0.8, 0.7, 0.6);
  light0->SetSpecularColor(0.2, 0.2, 0.2);
  root->AddChild(light0);

  // create spot light
  SpotLightPtr light1 = _scene->CreateSpotLight();
  light1->SetDiffuseColor(0.8, 0.8, 0.3);
  light1->SetSpecularColor(0.2, 0.2, 0.2);
  light1->SetLocalPosition(0, 3, 3);
  light1->SetDirection(1, -1, -1);
  root->AddChild(light1);

  // create point light
  PointLightPtr light2 = _scene->CreatePointLight();
  light2->SetDiffuseColor(0.2, 0.4, 0.8);
  light2->SetSpecularColor(0.2, 0.2, 0.2);
  light2->SetLocalPosition(3, 0, 2);
  root->AddChild(light2);

  // create camera
  CameraPtr camera = _scene->CreateCamera("camera");
  camera->SetLocalPosition(0.0, 0.0, 0.0);
  camera->SetLocalRotation(0.0, 0.0, 0.0);
  camera->SetImageWidth(800);
  camera->SetImageHeight(600);
  camera->SetAntiAliasing(2);
  camera->SetAspectRatio(1.333);
  camera->SetHFOV(M_PI / 2);
  root->AddChild(camera);
}

//////////////////////////////////////////////////
CameraPtr createCamera(const std::string &_engineName)
{
  // create and populate scene
  RenderEngine *engine = rendering::engine(_engineName);
  if (!engine)
  {
    std::cout << "Engine '" << _engineName
              << "' is not supported" << std::endl;
    return CameraPtr();
  }
  ScenePtr scene = engine->CreateScene("scene");
  buildScene(scene);

  // return camera sensor
  SensorPtr sensor = scene->SensorByName("camera");
  return std::dynamic_pointer_cast<Camera>(sensor);
}

//////////////////////////////////////////////////
int main(int _argc, char** _argv)
{
  glutInit(&_argc, _argv);

  common::Console::SetVerbosity(4);
  std::vector<std::string> engineNames;
  std::vector<CameraPtr> cameras;

  engineNames.push_back("ogre2");
  for (auto engineName : engineNames)
  {
    try
    {
      CameraPtr camera = createCamera(engineName);
      if (camera)
      {
        cameras.push_back(camera);
      }
    }
    catch (...)
    {
      // std::cout << ex.what() << std::endl;
      std::cerr << "Error starting up: " << engineName << std::endl;
    }
  }
  run(cameras);
  return 0;
}
