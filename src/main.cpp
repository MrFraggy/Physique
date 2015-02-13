#include <iostream>
#include <cstdlib>

#include <PartyKel/glm.hpp>
#include <PartyKel/WindowManager.hpp>

#include <PartyKel/renderer/Renderer3D.hpp>
#include <PartyKel/renderer/TrackballCamera.hpp>

#include <physic/modeleur.h>
#include <physic/forces/ressort.h>
#include <physic/forces/frein.h>
#include <physic/forces/constante.h>
#include <physic/forces/vent.h>
#include <physic/masses/libre.h>
#include <physic/masses/fixe.h>
#include <utility/clock.hpp>
#include "flag.hpp"
#include <graphic/shader.h>
#include <graphic/material.h>
#include <physic/masses/masses.h>

#include <vector>
#include <thread>
#include <sstream>
#include <ctime>

static const Uint32 WINDOW_WIDTH = 1024;
static const Uint32 WINDOW_HEIGHT = 768;

using namespace PartyKel;

typedef std::shared_ptr<Masse> MassePtr;

class CRenderer
{
public:
	CRenderer()
	{
		renderer.setProjMatrix(glm::perspective(70.f, float(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.f));
	}
	void clear()
	{
		renderer.clear();
	}

	void render()
	{
		renderer.drawParticles(positions.size(), 
								positions.data(),
								radius.data(),
								colors.data());
	}

	void setViewMatrix(const glm::mat4& m)
	{
		renderer.setViewMatrix(m);
	}

	void add(const glm::vec3& pos, float rad, const glm::vec3& color)
	{
		positions.push_back(pos);
        radius.push_back(rad);
        colors.push_back(color);
	}

    void addAll(const std::vector<glm::vec3> & pos, const std::vector<float>& rad, const std::vector<glm::vec3>& color)
    {
        positions.insert(positions.end(), pos.begin(), pos.end());
        radius.insert(radius.end(), rad.begin(), rad.end());
        colors.insert(colors.end(), color.begin(), color.end());
    }
protected:
	Renderer3D renderer;
	std::vector<glm::vec3> positions;
    std::vector<float> radius;
    std::vector<glm::vec3> colors;
};

int main(void)
{
    WindowManager wm(WINDOW_WIDTH, WINDOW_HEIGHT, "Newton was a Geek");
    wm.setFramerate(99999);
    std::srand(std::time(0));

    //Renderer3D renderer;
    //

    TrackballCamera camera;

    int mouseLastX, mouseLastY;

    // Temps s'écoulant entre chaque frame
    float elapsed = 0.f;
	bool done = false;
    bool wireframe = true;

    Modeleur modeleur;

    /////////////////////////////////////
    //  Pont / Ficelle 
    /////////////////////////////////////
    //*
    Masses& masses = modeleur.getMasses();
    masses.create(glm::vec3(-2.5,0,0), 1.f, true);
    masses.create(glm::vec3(-2.0,0,0), 1.f, false);
    masses.create(glm::vec3(-1.5,0,0), 1.f, false);
    masses.create(glm::vec3(-1.0,0,0), 1.f, false);
    masses.create(glm::vec3(-0.5,0,0), 1.f, false);
    masses.create(glm::vec3(-0.0,0,0), 1.f, false);
    masses.create(glm::vec3( 0.5,0,0), 1.f, false);
    masses.create(glm::vec3( 1.0,0,0), 1.f, false);
    masses.create(glm::vec3( 1.5,0,0), 1.f, false);
    masses.create(glm::vec3( 2.0,0,0), 1.f, false);
    masses.create(glm::vec3( 2.5,0,0), 1.f, true);

    SpringBreaks& springbreaks = modeleur.getSpringBreaks();
    springbreaks.create(0,1,0.5f);
    springbreaks.create(1,2,0.5f);
    springbreaks.create(2,3,0.5f);
    springbreaks.create(3,4,0.5f);
    springbreaks.create(4,5,0.5f);
    springbreaks.create(5,6,0.5f);
    springbreaks.create(6,7,0.5f);
    springbreaks.create(7,8,0.5f);
    springbreaks.create(8,9,0.5f);
    springbreaks.create(9,10,0.5f);
   
    //*/

    //////////////////////////////////////
    //  Drapeau
    //////////////////////////////////////
    /*
    const int height = 25;
    const int width = 25;

    Flag flag(25,25);
    auto masses = flag.getMasses();
    auto links = flag.getLinks();

    std::cout << "nb liaison : " << links.size() << std::endl;
    std::cout << "nb masses : " << masses.size() << std::endl;

    for(auto& m: masses)
        modeleur.addMasse(m);

    for(auto& l: links)
        modeleur.addLink(l);
    //*/
    CRenderer renderer;
    renderer.addAll(masses.getPositions(), masses.getRadius(), masses.getColors());

    //modeleur.addMacroForce(ForceConstantePtr(new ForceConstante(glm::vec3(0,G,0))));
    //modeleur.addMacroForce(VentPtr(new Vent(glm::vec3(20,1,1))));

    glm::mat4 proj = glm::perspective(70.f, WINDOW_WIDTH*1.f/WINDOW_HEIGHT, 0.1f, 100.f);
    Shader shader;
    shader.loadFromFile("../shaders/basic.vert", ShaderType_Vertex);
    shader.loadFromFile("../shaders/basic.frag", ShaderType_Fragment);
    shader.compile();

    Material texture;
    texture.loadFromFile("../images/pinup.jpg");

    Clock fpsClock;

    glClearColor(0.1,0.1,0.1,0);
    int mode = 2;
    int fps = 0, pps = 0;
    bool debug = false, simulate = false;

    std::thread physicThread([&modeleur, &done, &pps, &simulate]() {
        Uint32 lastTime = SDL_GetTicks();
        const uint32_t FrameDuration = 1000.f * dt;
        while(!done) {
            if(simulate)
                modeleur.update();

            Uint32 d = SDL_GetTicks() - lastTime;
            if(d < dt) {
                SDL_Delay(FrameDuration - d);
            }
            lastTime = SDL_GetTicks();
            ++pps;
        }
    });

    while(!done) {
        wm.startMainLoop();

        // Rendu
        glm::mat4 view = camera.getViewMatrix();
        renderer.setViewMatrix(view);
        renderer.clear();
        //if(debug)
            renderer.render();
        
        /*
        glEnable(GL_TEXTURE_2D);
        shader.bind();
        texture.bind();
        glm::mat4 mvp = proj*view;
        shader.send(Uniform_Matrix4f, "mvpMatrix", glm::value_ptr(mvp));
        flag.draw();
        texture.unbind();
        shader.unbind();
        glDisable(GL_TEXTURE_2D);
        */
        //particleManager.drawParticles(renderer);

        // Simulation
       // particleManager.move(dt * 0.01f);

        // Gestion des evenements
		SDL_Event e;
        while(wm.pollEvent(e)) {
			switch(e.type) {
				default:
					break;
				case SDL_QUIT:
					done = true;
					break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_SPACE) {
                        wireframe = !wireframe;
                    } else if(e.key.keysym.sym == SDLK_m) {
                        mode = (mode+1)%3;
                        //flag.setDrawMode(static_cast<DrawMode>(mode));
                    } else if(e.key.keysym.sym == SDLK_p)
                        debug = !debug;
                    else if(e.key.keysym.sym == SDLK_o)
                        simulate = !simulate;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_WHEELUP) {
                        camera.moveFront(0.1f);
                    } else if(e.button.button == SDL_BUTTON_WHEELDOWN) {
                        camera.moveFront(-0.1f);
                    } else if(e.button.button == SDL_BUTTON_LEFT) {
                        mouseLastX = e.button.x;
                        mouseLastY = e.button.y;
                    }
			}
		}

        int mouseX, mouseY;
        if(SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            float dX = mouseX - mouseLastX, dY = mouseY - mouseLastY;
            camera.rotateLeft(glm::radians(dX));
            camera.rotateUp(glm::radians(dY));
            mouseLastX = mouseX;
            mouseLastY = mouseY;
        }
        //flag.update();

        if(fpsClock.GetSeconds() > 1)
        {
            std::ostringstream oss;
            oss << "Flag - FPS: " << fps << " - PPS: " << pps;
            fps = 0; pps = 0;
            SDL_WM_SetCaption(oss.str().c_str(), 0);
            fpsClock.Restart();
        }
        ++fps;
        // Mise à jour de la fenêtre
        elapsed = wm.update();

	}

	physicThread.join();
}