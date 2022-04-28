/*
 * Copyright (C) 2022 Open Source Robotics Foundation
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

#ifndef IGNITION_RENDERING_OGRE_POINTLIGHTSHADOWCAMERASETUP_HH_
#define IGNITION_RENDERING_OGRE_POINTLIGHTSHADOWCAMERASETUP_HH_

#include "ignition/rendering/ogre/OgreNode.hh"
#include "ignition/rendering/ogre/OgreIncludes.hh"

namespace ignition
{
  namespace rendering
  {
    inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {
    //
    class IGNITION_RENDERING_OGRE_VISIBLE PointLightShadowCameraSetup
          : public Ogre::DefaultShadowCameraSetup
    {
      /// \brief Constructor
      public: PointLightShadowCameraSetup();

      /// \brief Destructor
      public: ~PointLightShadowCameraSetup();

      /// \brief Returns a shadow camera for a point light
      /// \sa FocusedShadowCameraSetup::getShadowCamera()
      public: virtual void getShadowCamera(const Ogre::SceneManager *_sm,
          const Ogre::Camera *_cam, const Ogre::Viewport *_vp,
          const Ogre::Light *_light, Ogre::Camera *_texCam, size_t _iteration)
          const override;
    };
    }
  }
}

#endif
