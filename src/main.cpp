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
		std::vector<glm::vec3> p;
		std::vector<float> m;
		std::vector<glm::vec3> c;
		for(auto& ma: masses)
		{
			p.push_back(ma->getPosition());
			m.push_back(ma->getMasse());
			c.push_back(ma->getColor());
		}

		renderer.drawParticles(p.size(), 
								p.data(),
								m.data(),
								c.data());
	}

	void setViewMatrix(const glm::mat4& m)
	{
		renderer.setViewMatrix(m);
	}

	void addMasse(const MassePtr& ptr)
	{
		masses.push_back(ptr);
	}
protected:
	Renderer3D renderer;
	std::vector<MassePtr> masses;
	std::vector<LinkPtr> links;
};

int main(void)
{
    WindowManager wm(WINDOW_WIDTH, WINDOW_HEIGHT, "Newton was a Geek");
    wm.setFramerate(30);
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
    /*
    std::vector<MassePtr> masses;
    masses.push_back(MassePtr(new MasseFixe(glm::vec3(-2.5,0,0))));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(-2,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(-1.5,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(-1,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(-0.5,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(0,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(0.5,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(1.0,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(1.5,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(2,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseLibre(glm::vec3(2.5,0,0), 1.f)));
    masses.push_back(MassePtr(new MasseFixe(glm::vec3(3,0,0))));

    std::vector<LinkPtr> links;
    links.push_back(getRessortFrein(masses.at(0).get(), masses.at(1).get()));
    links.push_back(getRessortFrein(masses.at(1).get(), masses.at(2).get()));
    links.push_back(getRessortFrein(masses.at(2).get(), masses.at(3).get()));
    links.push_back(getRessortFrein(masses.at(3).get(), masses.at(4).get()));
    links.push_back(getRessortFrein(masses.at(4).get(), masses.at(5).get()));
    links.push_back(getRessortFrein(masses.at(5).get(), masses.at(6).get()));
    links.push_back(getRessortFrein(masses.at(6).get(), masses.at(7).get()));
    links.push_back(getRessortFrein(masses.at(7).get(), masses.at(8).get()));
    links.push_back(getRessortFrein(masses.at(8).get(), masses.at(9).get()));
    links.push_back(getRessortFrein(masses.at(9).get(), masses.at(10).get()));
    links.push_back(getRessortFrein(masses.at(10).get(), masses.at(11).get()));
    */

    //////////////////////////////////////
    //  Drapeau
    //////////////////////////////////////

    const int height = 25;
    const int width = 25;
    
    /*std::vector<MassePtr> masses;
    
    for (int row = 0; row < height; ++row)
    {
        masses.push_back(MassePtr(new MasseFixe(glm::vec3(-width/2 * 0.1f, ((height / 2) - row) * 0.1f, 0))));
    }

    for(int col = 1; col < width; ++col)
    {
        for (int row = 0; row < height; ++row)
        {
            masses.push_back(MassePtr(new MasseLibre(glm::vec3(((-width/2) + col) * 0.1f, ((height / 2) - row)* 0.1f, 0), 1.f)));
        }
    }*/
    Flag flag(25,25);
    auto masses = flag.getMasses();
    auto links = flag.getLinks();

    std::cout << "nb liaison : " << links.size() << std::endl;
    std::cout << "nb masses : " << masses.size() << std::endl;

    for(auto& m: masses)
        modeleur.addMasse(m);

    for(auto& l: links)
        modeleur.addLink(l);

    CRenderer renderer;
    for(auto& m: masses)
        renderer.addMasse(m);

    modeleur.addMacroForce(ForceConstantePtr(new ForceConstante(glm::vec3(0,G,0))));
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
        if(debug)
            renderer.render();
        
        glEnable(GL_TEXTURE_2D);
        shader.bind();
        texture.bind();
        glm::mat4 mvp = proj*view;
        shader.send(Uniform_Matrix4f, "mvpMatrix", glm::value_ptr(mvp));
        flag.draw();
        texture.unbind();
        shader.unbind();
        glDisable(GL_TEXTURE_2D);
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
                        flag.setDrawMode(static_cast<DrawMode>(mode));
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
        flag.update();

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