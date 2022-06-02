/*
 * Copyright (C) 2015 Open Source Robotics Foundation
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
#include <ignition/rendering.hh>

#include "GlutWindow.hh"

using namespace ignition;
using namespace rendering;

//////////////////////////////////////////////////
void buildScene(ScenePtr _scene)
{
  // initialize _scene
  _scene->SetAmbientLight(0.3, 0.3, 0.3);
  // VisualPtr root = _scene->RootVisual(); No idea how to do this abstraction in luxcore

  // create directional light
  DirectionalLightPtr light0 = _scene->CreateDirectionalLight();
  // light0->SetDirection(-0.5, 0.5, -1);
  // light0->SetDiffuseColor(0.5, 0.5, 0.5);
  // light0->SetSpecularColor(0.5, 0.5, 0.5);
  // root->AddChild(light0);

  // create point light
  PointLightPtr light2 = _scene->CreatePointLight();
  // light2->SetDiffuseColor(0.5, 0.5, 0.5);
  // light2->SetSpecularColor(0.5, 0.5, 0.5);
  // light2->SetLocalPosition(3, 5, 5);
  // root->AddChild(light2);

  // create green material
  // MaterialPtr green = _scene->CreateMaterial();
  // green->SetAmbient(0.0, 0.5, 0.0);
  // green->SetDiffuse(0.0, 0.7, 0.0);
  // green->SetSpecular(0.5, 0.5, 0.5);
  // green->SetShininess(50);
  // green->SetReflectivity(0);


  // create center visual
  // VisualPtr cylinder = _scene->CreateVisual();
  // cylinder->AddGeometry(_scene->CreateCylinder());
  // cylinder->SetOrigin(0.0, -1.5, 0);
  // cylinder->SetLocalPosition(3, 0, 0);
  // cylinder->SetLocalScale(1, 1, 1);
  // cylinder->SetMaterial(green);
  // root->AddChild(cylinder);

//! [red material]
  // create red material
  // MaterialPtr red = _scene->CreateMaterial();
  // red->SetAmbient(0.5, 0.0, 0.0);
  // red->SetDiffuse(1.0, 0.0, 0.0);
  // red->SetSpecular(0.5, 0.5, 0.5);
  // red->SetShininess(50);
  // red->SetReflectivity(0);
  // red->SetRenderOrder(3);
//! [red material]

// create blue material
  // MaterialPtr blue = _scene->CreateMaterial();
  // blue->SetAmbient(0.0, 0.0, 0.3);
  // blue->SetDiffuse(0.0, 0.0, 0.8);
  // blue->SetSpecular(0.5, 0.5, 0.5);
  // blue->SetShininess(50);
  // blue->SetReflectivity(0);

  // create sphere visual
  // VisualPtr sphere = _scene->CreateVisual();
  // sphere->AddGeometry(_scene->CreateSphere());
  // sphere->SetOrigin(0.0, 1.5, 0);
  // sphere->SetLocalPosition(3, 0, 0);
  // sphere->SetLocalRotation(0, 0, 0);
  // sphere->SetLocalScale(1, 1, 1);
  // sphere->SetMaterial(blue);
  // root->AddChild(sphere);

  

  // create box visual
  // VisualPtr box = _scene->CreateVisual();
  // box->AddGeometry(_scene->CreateBox());
  // box->SetOrigin(0.0, 0, 0);
  // box->SetLocalPosition(3, 0, 0);
  // box->SetLocalScale(1, 1, 1);
  // box->SetMaterial(red);
  // root->AddChild(box);

//! [white material]
  // create white material
  // MaterialPtr white = _scene->CreateMaterial();
  // white->SetAmbient(0.5, 0.5, 0.5);
  // white->SetDiffuse(0.8, 0.8, 0.8);
  // white->SetReceiveShadows(true);
  // white->SetReflectivity(0);
  // white->SetRenderOrder(0);
//! [white material]

  // create plane visual
  // VisualPtr plane = _scene->CreateVisual();
  // plane->AddGeometry(_scene->CreatePlane());
  // plane->SetLocalScale(5, 8, 1);
  // plane->SetLocalPosition(3, 0, -0.5);
  // plane->SetMaterial(white);
  // root->AddChild(plane);

  // create camera
  CameraPtr camera = _scene->CreateCamera("camera");
  // camera->SetLocalPosition(0.0, 0.0, 0.0);
  // camera->SetLocalRotation(0.0, 0.0, 0.0);
  // camera->SetImageWidth(800);
  // camera->SetImageHeight(600);
  // camera->SetAntiAliasing(2);
  // camera->SetAspectRatio(1.333);
  // camera->SetHFOV(IGN_PI / 2);
  // root->AddChild(camera);

  // track target
  // camera->SetTrackTarget(box);
}

//////////////////////////////////////////////////
CameraPtr createCamera(const std::string &_engineName,
    const std::map<std::string, std::string>& _params)
{
  // create and populate scene
  RenderEngine *engine = rendering::engine(_engineName, _params);
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

  // Expose engine name to command line because we can't instantiate both
  // ogre and ogre2 at the same time
  std::string ogreEngineName("ogre");
  if (_argc > 1)
  {
    ogreEngineName = _argv[1];
  }

  GraphicsAPI graphicsApi = GraphicsAPI::OPENGL;
  if (_argc > 2)
  {
    graphicsApi = GraphicsAPIUtils::Set(std::string(_argv[2]));
  }

  common::Console::SetVerbosity(4);
  std::vector<std::string> engineNames;
  std::vector<CameraPtr> cameras;

  engineNames.push_back(ogreEngineName);

  for (auto engineName : engineNames)
  {
    try
    {
      std::map<std::string, std::string> params;
      if (engineName.compare("ogre2") == 0
          && graphicsApi == GraphicsAPI::METAL)
      {
        params["metal"] = "1";
      }

      CameraPtr camera = createCamera(engineName, params);
      if (camera)
      {
        cameras.push_back(camera);
      }
    }
    catch (std::exception & ex)
    {
      std::cout << ex.what() << std::endl;
      // std::cerr << "Error starting up: " << engineName << std::endl;
    }
  }
  run(cameras);
  return 0;
}
