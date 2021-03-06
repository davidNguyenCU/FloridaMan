#ifndef GAME_H_
#define GAME_H_

#include <exception>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>

#include "camera.h"
#include "entity_structure.h"
#include "particle_node.h"
#include "player.h"
#include "resource_manager.h"
#include "scene_graph.h"

#include "scene_node.h"
#include "utilities.h"

namespace game
{
// Exception type for the game
class GameException : public std::exception
{
private:
    std::string message_;

public:
    GameException(std::string message)
        : message_(message){};
    virtual const char *what() const throw() { return message_.c_str(); };
    virtual ~GameException() throw(){};
};

// Game application
class Game
{
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
    //Return the Scene Graph
    SceneGraph *GetGraph();
    void AddNode(SceneNode *scn);
    Camera *GetCamera(void);
    Player *GetPlayer(void);
    void AddPoints(int points);
    void AirshipKilled();
    void CybertruckKilled();
    void TurretKilled();
    SceneNode *CreateEntity(int type, glm::vec3 pos, glm::vec3 scale);

    //A callback function for the keys that we don't need to get constant input from
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void AlienFreed();

private:
    // GLFW window
    GLFWwindow *window_;

    // Scene graph containing all nodes to render
    SceneGraph scene_;

    int alienCounter = 0;
    // Resources available to the game
    ResourceManager resman_;

    // Camera abstraction
    Camera camera_;

    // Skybox
    SceneNode *skybox_;

    //Player
    Player *player_;

    // Flag to turn animation on/off
    bool animating_;

    int count_;

    // Methods to initialize the game
    void InitWindow(void);
    void InitView(void);
    void InitEventHandlers(void);

    int turretsKilled;
    int trucksKilled;
    int airshipsKilled;
    int m_points;

    void GetKeyStates(GLFWwindow *window);
    static void ResizeCallback(GLFWwindow *window, int width, int height);

    // Create an instance of an object stored in the resource manager
    SceneNode *CreateInstance(int type, std::string entity_name, std::string object_name, std::string material_name, std::string texture_name = std::string(""), std::string envmap_name = std::string(""));

    void CreateTowerField(void);
}; // class Game

} // namespace game

#endif // GAME_H_
