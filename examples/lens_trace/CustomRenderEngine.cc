/*
 * Copyright (C) 2021 Open Source Robotics Foundation
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

#include <ignition/common/SingletonT.hh>

#include <ignition/plugin/Register.hh>

#include "ignition/rendering/RenderEnginePlugin.hh"
#include "ignition/rendering/base/BaseRenderEngine.hh"
#include "ignition/rendering/base/BaseScene.hh"
#include "ignition/rendering/base/BaseCamera.hh"
#include "ignition/rendering/base/BaseSensor.hh"
#include "ignition/rendering/base/BaseNode.hh"
#include "ignition/rendering/base/BaseObject.hh"
#include "ignition/rendering/base/BaseMaterial.hh"
#include "LensTraceEngineRenderTypes.hh"

using namespace ignition;
using namespace rendering;

namespace ignition
{

namespace rendering
{

inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {

  class LensTraceEngineObject:
    public BaseObject
  {
    protected: LensTraceEngineObject() {}

    public: virtual ~LensTraceEngineObject() {}
    
    // This functions seems to be the issue, but for some reason i cant return this->scene
    public: virtual ScenePtr Scene() const
    {
      // line 59 triggers this, for some reason upclass casting does not work
      // error: could not convert ‘((const ignition::rendering::v5::LensTraceEngineObject*)this)->
      // ignition::rendering::v5::LensTraceEngineObject::scene’ 
      // from ‘shared_ptr<ignition::rendering::v5::LensTraceEngineScene>’ to ‘shared_ptr<ignition::rendering::v5::Scene>’
      // return this->scene;
      return nullptr;
    }

    protected: LensTraceEngineScenePtr scene;

    private: friend class LensTraceEngineScene;
  };

  class LensTraceEngineMaterial :
    public BaseMaterial<LensTraceEngineObject>
  {
    protected: LensTraceEngineMaterial() {}

    public: virtual ~LensTraceEngineMaterial() {}

    private: friend class LensTraceEngineScene;
  };

  class LensTraceEngineRenderTarget :
      public virtual BaseRenderTarget<LensTraceEngineObject>
  {
    protected: LensTraceEngineRenderTarget() : hostData(0) {}

    public: virtual ~LensTraceEngineRenderTarget() {}

    public: virtual void Copy(Image &_image) const
    {
      if (_image.Width() != this->width || _image.Height() != this->height)
      {
        ignerr << "Invalid image dimensions" << std::endl;
        return;
      }

      unsigned char *imageData = _image.Data<unsigned char>();

      for (unsigned int y = 0; y < this->height; y++) {
        for (unsigned int x = 0; x < this->width; x++) {
          imageData[(3 * (y * width + x)) + 0] = 255;
          imageData[(3 * (y * width + x)) + 1] = 155;
          imageData[(3 * (y * width + x)) + 2] = 55;
        }
      }
    }

    protected: unsigned int MemorySize() const;

    protected: virtual void RebuildImpl() 
    {
      delete this->hostData;
      unsigned int count = this->width * this->height * 3;
      this->hostData = new float[count];
    }

    protected: float *hostData;

    private: friend class LensTraceEngineCamera;
  };

  class LensTraceEngineNode :
    public BaseNode<LensTraceEngineObject>
  {
    protected: LensTraceEngineNode() {}

    public: virtual ~LensTraceEngineNode() {}

    public: virtual bool HasParent() const override
    {
     return true;
    }

    public: virtual NodePtr Parent() const override
    {
      return nullptr;
    }

    public: virtual void PreRender() override {}

      // Documentation inherited.
    public: virtual math::Vector3d LocalScale() const override 
    {
      return math::Vector3d::One;
    }

      // Documentation inherited.
    public: virtual bool InheritScale() const override 
    {
      return true;
    }

      // Documentation inherited.
    public: virtual void SetInheritScale(bool _inherit) override {}

      // Documentation inherited.
    protected: virtual void SetLocalScaleImpl(
                     const math::Vector3d &_scale) override {}

    protected: virtual math::Pose3d RawLocalPose() const override 
    {
      return math::Pose3d::Zero;
    }

    protected: virtual void SetRawLocalPose(const math::Pose3d &_pose) override {}

    protected: virtual void WritePoseToDevice() {}

    protected: virtual void WritePoseToDeviceImpl() {}

    protected: virtual void SetParent(LensTraceEngineNodePtr _parent) {}

    protected: virtual void Init() {}

    protected: virtual NodeStorePtr Children() const override 
    {
      return nullptr;
    }

    protected: virtual bool AttachChild(NodePtr _child) override
    {
      return true;
    }

    protected: virtual bool DetachChild(NodePtr _child) override
    {
      return true;
    }

    protected: LensTraceEngineNodePtr parent;

    protected: math::Pose3d pose;

    protected: bool poseDirty;

    // protected: LuxCoreStorePtr children;

    protected: math::Vector3d scale = math::Vector3d::One;

    protected: bool inheritScale = true;
  };

  class LensTraceEngineSensor :
    public BaseSensor<LensTraceEngineNode>
  {
    protected: LensTraceEngineSensor() {}

    public: virtual ~LensTraceEngineSensor() {}
  };

  class LensTraceEngineCamera :
    public BaseCamera<LensTraceEngineSensor>
  {
    protected: LensTraceEngineCamera()
    {
      this->renderTarget = LensTraceEngineRenderTargetPtr(new LensTraceEngineRenderTarget);
      this->renderTarget->SetFormat(PF_R8G8B8);
    };

    public: virtual ~LensTraceEngineCamera() {};

    public: virtual void Render() {};

    public: virtual void Update() {};

    protected: virtual RenderTargetPtr RenderTarget() const 
    {
      return this->renderTarget;
    };

    protected: LensTraceEngineRenderTargetPtr renderTarget;

    private: friend class LensTraceEngineScene;
  };

  class LensTraceEngineScene :
    public BaseScene
  {
    protected: LensTraceEngineScene(unsigned int _id, const std::string &_name) : BaseScene(_id, _name) 
    {
      this->id_ = _id;
      this->name_ = _name;
    }

    public: virtual ~LensTraceEngineScene() {}

    public: virtual void Fini() {}

    public: virtual RenderEngine *Engine() const 
    {
      ignerr << "engine() was called 246" << std::endl;
      // return LensTraceEngineRenderEngine::Instance();
      return nullptr;
    }

    public: virtual VisualPtr RootVisual() const 
    {
      return nullptr;
    }

    public: virtual math::Color AmbientLight() const 
    {
      return math::Color::Black;
    }

    public: virtual void SetAmbientLight(const math::Color &_color) 
    {

    }

    protected: virtual DirectionalLightPtr CreateDirectionalLightImpl(
                     unsigned int _id, const std::string &_name) 
    {
      return nullptr;
    }

    protected: virtual PointLightPtr CreatePointLightImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual SpotLightPtr CreateSpotLightImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual CameraPtr CreateCameraImpl(unsigned int _id,
                     const std::string &_name)
    {
      LensTraceEngineCameraPtr camera(new LensTraceEngineCamera);
      bool result = this->InitObject(camera, _id, _name);
      return (result) ? camera : nullptr;
    }

    protected: virtual DepthCameraPtr CreateDepthCameraImpl(unsigned int _id,
                     const std::string &_name) override
    {
      return nullptr;
    }

    protected: virtual VisualPtr CreateVisualImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual ArrowVisualPtr CreateArrowVisualImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual AxisVisualPtr CreateAxisVisualImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual GeometryPtr CreateBoxImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual GeometryPtr CreateConeImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual GeometryPtr CreateCylinderImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual GeometryPtr CreatePlaneImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual GeometryPtr CreateSphereImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual MeshPtr CreateMeshImpl(unsigned int _id,
                     const std::string &_name, const std::string &_meshName)
    {
      return nullptr;
    }

    protected: virtual MeshPtr CreateMeshImpl(unsigned int _id,
                     const std::string &_name, const MeshDescriptor &_desc)
    {
      return nullptr;
    }

    protected: virtual CapsulePtr CreateCapsuleImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual GridPtr CreateGridImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual MarkerPtr CreateMarkerImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual LidarVisualPtr CreateLidarVisualImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual HeightmapPtr CreateHeightmapImpl(unsigned int _id,
                     const std::string &_name,
                     const HeightmapDescriptor &_desc)
    {
      return nullptr;
    }

    protected: virtual WireBoxPtr CreateWireBoxImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual MaterialPtr CreateMaterialImpl(unsigned int _id,
                     const std::string &_name)
    {
      LensTraceEngineMaterialPtr material(new LensTraceEngineMaterial);
      bool result = this->InitObject(material, _id, _name);
      return (result) ? material : nullptr;
    }

    protected: virtual RenderTexturePtr CreateRenderTextureImpl(
                     unsigned int _id, const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual RenderWindowPtr CreateRenderWindowImpl(
                     unsigned int _id, const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual RayQueryPtr CreateRayQueryImpl(
                     unsigned int _id, const std::string &_name)
    {
      return nullptr;
    }

    protected: virtual LightStorePtr Lights() const
    {
      return nullptr;
    }

    protected: virtual SensorStorePtr Sensors() const
    {
      return this->sensors;
    }

    protected: virtual VisualStorePtr Visuals() const
    {
      return nullptr;
    }

    protected: virtual MaterialMapPtr Materials() const
    {
      return this->materials;
    }

    protected: virtual bool LoadImpl()
    {
      ignerr << "LoadImpl" << std::endl;
      return true;
    }

    protected: virtual bool InitImpl()
    {
      ignerr << "InitImpl" << std::endl;
      this->CreateStores();
      return true;
    }

    public: virtual bool IsInitialized() 
    {
      return true;
    }

    public: virtual unsigned int Id() 
    {
      return this->id_;
    }

    public: virtual std::string Name() 
    {
      return this->name_;
    }

    ignition::rendering::LightVisualPtr CreateLightVisualImpl(unsigned int _id,
                     const std::string &_name)
    {
      return nullptr;
    }

    protected: void CreateStores()
    {
      // this->lights = OptixLightStorePtr(new OptixLightStore);
      this->sensors = LensTraceEngineSensorStorePtr(new LensTraceEngineSensorStore);
      // this->visuals = OptixVisualStorePtr(new OptixVisualStore);
      this->materials = LensTraceEngineMaterialMapPtr(new LensTraceEngineMaterialMap);
    }

    protected: bool InitObject(LensTraceEngineObjectPtr _object, unsigned int _id,
    const std::string &_name)
    {
      // assign needed varibles
      _object->id = _id;
      _object->name = _name;
      _object->scene = this->SharedThis();

      // initialize object
      _object->Load();
      _object->Init();

      return true;
    }

    private: LensTraceEngineScenePtr SharedThis()
    {
      ScenePtr sharedBase = this->shared_from_this();
      return std::dynamic_pointer_cast<LensTraceEngineScene>(sharedBase);
    }

    protected: unsigned int id_;
    protected: std::string name_;

    protected: LensTraceEngineMaterialMapPtr materials;
    protected: LensTraceEngineSensorStorePtr sensors;

    private: friend class LensTraceEngineRenderEngine;

  };


  /// \brief The render engine class which implements a render engine.
  class LensTraceEngineRenderEngine :
    public virtual BaseRenderEngine,
    public common::SingletonT<LensTraceEngineRenderEngine>
  {
    // Documentation Inherited.
    public: virtual bool IsEnabled() const override
    {
      return true;
    }

    // Documentation Inherited.
    public: virtual std::string Name() const override
    {
      return "LensTraceEngineRenderEngine";
    }

    // Documentation Inherited.
    protected: virtual bool LoadImpl(const std::map<std::string,
                   std::string> &/*_params*/) override
    {
      return true;
    }

    /// \brief Initialize the render engine.
    /// \return True if the operation is successful
    protected: virtual bool InitImpl() override
    {
      this->scenes = LensTraceEngineSceneStorePtr(new LensTraceEngineSceneStore);
      return true;
    }

    /// \brief Get a pointer to the list of scenes managed by the render
    /// engine.
    /// \return list of scenes
    protected: virtual SceneStorePtr Scenes()
                     const override
    {
      return this->scenes;
    }

    /// \brief Create a scene.
    /// \param[in] _id Unique scene Id
    /// \parampin] _name Name of scene
    protected: virtual ScenePtr
                   CreateSceneImpl(unsigned int _id,
                   const std::string &_name) override
    {
      auto scene = LensTraceEngineScenePtr(new LensTraceEngineScene(_id, _name));
      this->scenes->Add(scene);
      return scene;
    }

    /// \brief Singelton setup.
    private: friend class common::SingletonT<LensTraceEngineRenderEngine>;
    private: LensTraceEngineSceneStorePtr scenes;
  };

  /// \brief Plugin for loading the HelloWorld render engine.
  class LensTraceEnginePlugin :
    public RenderEnginePlugin
  {
    /// \brief Get the name of the render engine loaded by this plugin.
    /// \return Name of render engine
    public: std::string Name() const override
    {
      return LensTraceEngineRenderEngine::Instance()->Name();
    }

    /// \brief Get a pointer to the render engine loaded by this plugin.
    /// \return Render engine instance
    public: RenderEngine *Engine() const override
    {
      return LensTraceEngineRenderEngine::Instance();
    }
  };

}

}

}

// Register this plugin
IGNITION_ADD_PLUGIN(ignition::rendering::LensTraceEnginePlugin,
                    ignition::rendering::RenderEnginePlugin)
