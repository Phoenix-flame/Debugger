#include <Phoenix/core/layer.h>
#include <Phoenix/renderer/shader.h>
#include <Phoenix/event/keyEvent.h>
#include <Phoenix/core/application.h>
#include <Phoenix/imGui/imgui.h>
#include <Phoenix/renderer/CameraController.h>
#include <Phoenix/renderer/Framebuffer.h>
#include <Phoenix/renderer/renderer_command.h>
#include <Phoenix/Scene/Scene.h>
#include <Phoenix/event/keyEvent.h>
#include "Worker.h"

using namespace Phoenix;



class MainLayer: public Layer{
public:
    MainLayer(const std::string& name = "Layer");
    ~MainLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(Timestep ts) override;
    virtual void OnEvent(Event& e) override;
    virtual void OnImGuiRender() override;

private:
    bool OnResize(WindowResizeEvent& e){
        m_ViewportSize.x = (float)e.GetWidth();
        m_ViewportSize.y = (float)e.GetHeight();
        return false;
    }
    bool OnKeyPressed(KeyPressedEvent& e);

private:
    bool vsync = true;
private:
    Ref<Framebuffer> m_Framebuffer;
    bool m_ViewportFocused = false, m_ViewportHovered = false;
    glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
    
    glm::vec3 m_BackgroundColor = { 71./255., 222./255., 78./255. };
    EditorCamera m_MainCamera;
    Ref<Phoenix::Scene> m_Scene;


    bool m_OverlayEnabled = true;
    Ref<Worker> m_Worker;
    
};