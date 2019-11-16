#ifndef GAME_H_
#define GAME_H_

#include <exception>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>

#include "scene_graph.h"
#include "resource_manager.h"
#include "camera.h"
#include "asteroid.h"

#include "mine.h"
#include "air_entity.h"


namespace game {

	enum EntityType { Static, Ground, Air, MineInstance, Default=-1 };


    // Exception type for the game
    class GameException: public std::exception
    {
        private:
            std::string message_;
        public:
            GameException(std::string message) : message_(message) {};
            virtual const char* what() const throw() { return message_.c_str(); };
            virtual ~GameException() throw() {};
    };

    // Game application
    class Game {

        public:
            // Constructor and destructor
            Game(void);
            ~Game();
            // Call Init() before calling any other method
            void Init(void); 
            // Set up resources for the game
            void SetupResources(void);
            // Set up initial scene
            void SetupScene(void);
            // Run the game: keep the application active
            void MainLoop(void); 

        private:
            // GLFW window
            GLFWwindow* window_;

            // Scene graph containing all nodes to render
            SceneGraph scene_;

            // Resources available to the game
            ResourceManager resman_;

            // Camera abstraction
            Camera camera_;

            // Skybox
            SceneNode *skybox_;

            // Flag to turn animation on/off
            bool animating_;

			int count_;

            // Methods to initialize the game
            void InitWindow(void);
            void InitView(void);
            void InitEventHandlers(void);
 
            // Methods to handle events
            //static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            
			void GetKeyStates(GLFWwindow* window);
            static void ResizeCallback(GLFWwindow* window, int width, int height);

            // Asteroid field
            // Create instance of one asteroid
            Asteroid *CreateAsteroidInstance(std::string entity_name, std::string object_name, std::string material_name);
            // Create entire random asteroid field
            void CreateAsteroidField(int num_asteroids = 1500);

            // Create an instance of an object stored in the resource manager
			SceneNode *CreateInstance(int type, std::string entity_name, std::string object_name, std::string material_name, std::string texture_name = std::string(""), std::string envmap_name = std::string(""));
			void CreateEntity(int type, glm::vec3 pos, glm::vec3 scale);

    }; // class Game

} // namespace game

#endif // GAME_H_
