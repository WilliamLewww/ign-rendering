#ifndef IGNITION_RENDERING_LUXCOREENGINE_LUXCOREENGINELIGHT_HH_
#define IGNITION_RENDERING_LUXCOREENGINE_LUXCOREENGINELIGHT_HH_

#include "ignition/rendering/base/BaseLight.hh"

#include "LuxCoreEngineRenderTypes.hh"
#include "LuxCoreEngineNode.hh"

#include "luxcore/luxcore.h"

namespace ignition
{
  namespace rendering
  {
    inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {
    class LuxCoreEngineLight :
      public BaseLight<LuxCoreEngineNode>
    {
      public: virtual ignition::math::Color DiffuseColor() const;

      public: virtual void SetDiffuseColor(double _r, double _g, double _b,
                  double _a = 1.0);

      public: virtual void SetDiffuseColor(
          const ignition::math::Color &_color);

      public: virtual ignition::math::Color SpecularColor() const;

      public: virtual void SetSpecularColor(
          const ignition::math::Color &_color);

      public: virtual double AttenuationConstant() const;

      public: virtual void SetAttenuationConstant(double _value);

      public: virtual double AttenuationLinear() const;

      public: virtual void SetAttenuationLinear(double _value);

      public: virtual double AttenuationQuadratic() const;

      public: virtual void SetAttenuationQuadratic(double _value);

      public: virtual double AttenuationRange() const;

      public: virtual void SetAttenuationRange(double _range);

      public: virtual bool CastShadows() const;

      public: virtual void SetCastShadows(bool _castShadows);

      public: virtual double Intensity() const;

      public: virtual void SetIntensity(double _intensity);

      protected: std::string lightType;

      protected: float gainR, gainG, gainB;

      protected: float directionX, directionY, directionZ;
    };
    class LuxCoreEngineDirectionalLight :
      public BaseDirectionalLight<LuxCoreEngineLight>
    {
      public: LuxCoreEngineDirectionalLight(std::string lightType);
      
      public: virtual math::Vector3d Direction() const;

      public: virtual void SetDirection(double _x, double _y, double _z);

      public: virtual void SetDirection(const math::Vector3d &_dir);
    };
    }
  }
}

#endif
