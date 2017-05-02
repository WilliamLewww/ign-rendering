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
#ifndef IGNITION_RENDERING_OGRE_OGRECONVERSIONS_HH_
#define IGNITION_RENDERING_OGRE_OGRECONVERSIONS_HH_

#include <ignition/math/Color.hh>
#include <ignition/math/Quaternion.hh>
#include <ignition/math/Vector3.hh>

#include "ignition/rendering/PixelFormat.hh"
#include "ignition/rendering/ogre/OgreIncludes.hh"
#include "ignition/rendering/Util.hh"

namespace ignition
{
  namespace rendering
  {
    /// \addtogroup ign_rendering
    /// \{

    /// \brief Conversions Conversions.hh rendering/Conversions.hh
    /// \brief A set of utility function to convert between Gazebo and Ogre
    /// data types
    class IGNITION_VISIBLE OgreConversions
    {
      /// \brief Return the equivalent ogre color
      /// \param[in] _color ign-math color to convert
      /// \return Ogre color value
      public: static Ogre::ColourValue Convert(
          const math::Color &_color);

      /// \brief Return the equivalent ign-math color
      /// \param[in] _color Ogre color to convert
      /// \return ign-math color value
      public: static math::Color Convert(
          const Ogre::ColourValue &_color);

      /// \brief return Ogre Vector from ign-math Vector3
      /// \param[in] _vector ign-math vector
      /// \return Ogre vector
      public: static Ogre::Vector3 Convert(const math::Vector3d &_vector);

      /// \brief return ign-math Vector from ogre Vector3
      /// \param[in] _vector Ogre vector
      /// \return ign-math vector
      public: static math::Vector3d Convert(const Ogre::Vector3 &_vector);

      /// \brief Ign-math quaternion to Ogre quaternion
      /// \param[in] _quat ign-math quaternion
      /// \return Ogre quaternion
      public: static Ogre::Quaternion Convert(const math::Quaterniond &_quat);

      /// \brief Ogre quaternion to ign-math quaternion
      /// \param[in] _quat Ogre quaternion
      /// return ign-math quaternion
      public: static math::Quaterniond Convert(const Ogre::Quaternion &_quat);

      /// \brief Ign-math angle to Ogre angle
      /// \param[in] _angle ign-math angle
      /// \return Ogre angle
      public: static Ogre::Radian Convert(const math::Angle &_angle);

      /// \brief Ogre angle to ign-math angle
      /// \param[in] _angle Ogre angle
      /// return Ign-math angle
      public: static math::Angle Convert(const Ogre::Radian &_angle);

      /// \brief Ign-rendering PixelFormat to Ogre PixelFormat
      /// \param[in] _v Ign-rendering PixelFormat
      /// return Ogre PixelFormat
      public: static Ogre::PixelFormat Convert(PixelFormat _format);

      private: static const Ogre::PixelFormat ogrePixelFormats[PF_COUNT];
    };

    /// \}
  }
}
#endif
