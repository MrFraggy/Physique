#include <iostream>
#include <cstdlib>

#include <PartyKel/glm.hpp>
#include <PartyKel/WindowManager.hpp>

#include <PartyKel/renderer/Renderer3D.hpp>
#include <PartyKel/renderer/TrackballCamera.hpp>

#include <physic/modeleur.h>
#include <vector>
#include <thread>

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

    // Création des particules
   /* StaticParticleManager particleManager;
    particleManager.addParticle(glm::vec3(0), 1, glm::vec3(1, 1, 1));
    particleManager.addCircleParticles(0.5f, 128);
*/
    //Renderer3D renderer;
    //

    TrackballCamera camera;
    int mouseLastX, mouseLastY;

    // Temps s'écoulant entre chaque frame
    float elapsed = 0.f;
	bool done = false;
    bool wireframe = true;

    Modeleur modeleur;

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

    for(auto& m: masses)
        modeleur.addMasse(m);

    for(auto& l: links)
        modeleur.addLink(l);

    CRenderer renderer;
    for(auto& m: masses)
        renderer.addMasse(m);

    std::thread physicThread([&modeleur, &done]() {

    	Uint32 lastTime = SDL_GetTicks();

    	const uint32_t FrameDuration = 1000.f * dt;
    	while(!done) {
    		modeleur.update();

		    Uint32 d = SDL_GetTicks() - lastTime;
		    if(d < dt) {
		        SDL_Delay(FrameDuration - d);
		    }
		    lastTime = SDL_GetTicks();
    	}
    });

    while(!done) {
        wm.startMainLoop();

        // Rendu
        renderer.setViewMatrix(camera.getViewMatrix());
        renderer.clear();
        renderer.render();

        
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
                    }
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

        // Mise à jour de la fenêtre
        elapsed = wm.update();
	}

	physicThread.join();
}