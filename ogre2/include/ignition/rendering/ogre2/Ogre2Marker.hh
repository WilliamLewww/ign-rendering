/*
 * Copyright (C) 2019 Open Source Robotics Foundation
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

#ifndef IGNITION_RENDERING_OGRE2_OGREMARKER_HH_
#define IGNITION_RENDERING_OGRE2_OGREMARKER_HH_

#include <memory>
#include "ignition/rendering/base/BaseMarker.hh"
#include "ignition/rendering/ogre2/Ogre2Geometry.hh"

namespace ignition
{
  namespace rendering
  {
    inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {
    //
    // Forward declaration
    class Ogre2MarkerPrivate;

    /// \brief Ogre 2.x implementation of a marker geometry.
    class IGNITION_RENDERING_OGRE2_VISIBLE Ogre2Marker
      : public BaseMarker<Ogre2Geometry>
    {
      /// \brief Constructor
      protected: Ogre2Marker();

      /// \brief Destructor
      public: virtual ~Ogre2Marker();

      // Documentation inherited.
      public: virtual void Init() override;

      // Documentation inherited.
      public: virtual void PreRender() override;

      // Documentation inherited.
      public: virtual void Destroy() override;

      // Documentation inherited.
      public: virtual Ogre::MovableObject *OgreObject() const override;

      // Documentation inherited.
      public: virtual MaterialPtr Material() const override;

      // Documentation inherited.
      public: virtual void SetMaterial(
                           MaterialPtr _material, bool _unique) override;

      // Documentation inherited
      public: virtual void SetPoint(unsigned int _index,
                           const ignition::math::Vector3d &_value) override;

      // Documentation inherited
      public: virtual void AddPoint(const ignition::math::Vector3d &_pt,
                           const ignition::math::Color &_color) override;

      // Documentation inherited
      public: virtual void ClearPoints() override;

      // Documentation inherited
      public: virtual void SetType(const MarkerType _markerType) override;

      // Documentation inherited
      public: virtual MarkerType Type() const override;

      /// \brief Create the marker geometry in ogre
      private: void Create();

      /// \brief Marker should only be created by scene.
      private: friend class Ogre2Scene;

      /// \brief Private data class
      private: std::unique_ptr<Ogre2MarkerPrivate> dataPtr;
    };
    }
  }
}
#endif
