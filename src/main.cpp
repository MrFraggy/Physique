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
typedef std::shared_ptr<Link> LinkPtr;

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


    MassePtr masse1(new MasseFixe(glm::vec3(-2,0,0)));
    MassePtr masse2(new MasseLibre(glm::vec3(-1.5,0,0), 1.f));
    MassePtr masse3(new MasseLibre(glm::vec3(-1,0,0), 1.f));
    MassePtr masse4(new MasseLibre(glm::vec3(-0.5,0,0), 1.f));
    MassePtr masse5(new MasseLibre(glm::vec3(0,0,0), 1.f));
    MassePtr masse6(new MasseLibre(glm::vec3(0.5,0,0), 1.f));
    MassePtr masse7(new MasseLibre(glm::vec3(1.,0,0), 1.f));
    MassePtr masse8(new MasseLibre(glm::vec3(1.5,0,0), 1.f));
    MassePtr masse9(new MasseLibre(glm::vec3(2,0,0), 1.f));
    MassePtr masse10(new MasseLibre(glm::vec3(2.5,0,0), 1.f));
    MassePtr masse11(new MasseLibre(glm::vec3(3,0,0), 1.f));
    MassePtr masse12(new MasseFixe(glm::vec3(3.5,0,0)));

    LinkPtr link1(new RessortLink(masse1.get(), masse2.get()));
    LinkPtr link2(new RessortLink(masse2.get(), masse3.get()));
    LinkPtr link3(new RessortLink(masse3.get(), masse4.get()));
    LinkPtr link4(new RessortLink(masse4.get(), masse5.get()));
    LinkPtr link5(new RessortLink(masse5.get(), masse6.get()));
    LinkPtr link6(new RessortLink(masse6.get(), masse7.get()));
    LinkPtr link7(new RessortLink(masse7.get(), masse8.get()));
    LinkPtr link8(new RessortLink(masse8.get(), masse9.get()));
    LinkPtr link9(new RessortLink(masse9.get(), masse10.get()));
    LinkPtr link10(new RessortLink(masse10.get(), masse11.get()));
    LinkPtr link11(new RessortLink(masse11.get(), masse12.get()));

    modeleur.addMasse(masse1);
    modeleur.addMasse(masse2);
    modeleur.addMasse(masse3);
    modeleur.addMasse(masse4);  
    modeleur.addMasse(masse5);  
    modeleur.addMasse(masse6);  
    modeleur.addMasse(masse7);  
    modeleur.addMasse(masse8);  
    modeleur.addMasse(masse9);  
    modeleur.addMasse(masse10);  
    modeleur.addMasse(masse11);  
    modeleur.addMasse(masse12);  

    modeleur.addLink(link1);
    modeleur.addLink(link2);
    modeleur.addLink(link3);
    modeleur.addLink(link4);
    modeleur.addLink(link5);
    modeleur.addLink(link6);
    modeleur.addLink(link7);
    modeleur.addLink(link8);
    modeleur.addLink(link9);
    modeleur.addLink(link10);
    modeleur.addLink(link11);

    CRenderer renderer;
    renderer.addMasse(masse1);
    renderer.addMasse(masse2);
    renderer.addMasse(masse3);
    renderer.addMasse(masse4);
    renderer.addMasse(masse5);
    renderer.addMasse(masse6);
    renderer.addMasse(masse7);
    renderer.addMasse(masse8);
    renderer.addMasse(masse9);
    renderer.addMasse(masse10);
    renderer.addMasse(masse11);
    renderer.addMasse(masse12);

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