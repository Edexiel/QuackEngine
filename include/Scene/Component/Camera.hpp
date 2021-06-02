#ifndef QUACKENGINE_CAMERA_HPP
#define QUACKENGINE_CAMERA_HPP

#include "Maths/Matrix4.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Quaternion.hpp"

#include "Renderer/Framebuffer.hpp"
#include "Scene/Component/ComponentBase.hpp"

namespace Input
{
    class InputManager;
};

class CameraSystem;

namespace Component
{
    class Camera : public ComponentBase
    {

    private:
        unsigned int _width{0};
        unsigned int _height{0};

        float _far{0};
        float _near{0};

        Renderer::Framebuffer _framebuffer{};

        Maths::Matrix4 _projection;
        Maths::Matrix4 _view;

    public:

        bool isActive{true};

        friend ::CameraSystem;
        float _fov{50};
        bool _isPerspective{true};

        Camera() = default;
        Camera(unsigned int width, unsigned int height, float far, float near, float fov);

        void Resize(unsigned int width, unsigned int height);

        Renderer::Framebuffer GetFramebuffer() const;

        const Maths::Matrix4 &GetProjection() const;
        const Maths::Matrix4 &GetView() const;

        void SetProjection(unsigned int width, unsigned int height, float far, float near,
                           float fov);
        void SetProjection(unsigned int width, unsigned int height, float far, float near);
        void CreateProjection();
        void SetView(const Maths::Matrix4 &view);

        /****** Serialization *******/

        private:
            void LoadFramebuffer();

        friend class cereal::access;

        template<class Archive>
        void save(Archive &archive) const
        {
            archive(CEREAL_NVP(isActive), CEREAL_NVP(_width), CEREAL_NVP(_height), CEREAL_NVP(_far), CEREAL_NVP(_near),
                    CEREAL_NVP(_fov));
        }

        template<class Archive>
        void load(Archive &archive)
        {
            archive(CEREAL_NVP(isActive), CEREAL_NVP(_width), CEREAL_NVP(_height), CEREAL_NVP(_far), CEREAL_NVP(_near),
                    CEREAL_NVP(_fov));

            if (_isPerspective)
                _projection = Maths::Matrix4::Perspective(_width, _height, _near, _far, _fov);
            else
                _projection = Maths::Matrix4::OrthoMatrix(_width, _height, _near, _far);

            _view = Maths::Matrix4::Identity();
            LoadFramebuffer();
        }

    };
}
#endif // QUACKENGINE_CAMERA_HPP
