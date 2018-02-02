#pragma once
#ifndef _ENGINE_APP_HPP_
#define _ENGINE_APP_HPP_

#include "IO/Window.hpp"
#include "Loader/Loader.hpp"
#include "Scene/Scene.hpp"

#include <string>

class EngineApp {
    public:
        EngineApp();

        Scene scene;

        int init();
        void run();
        void terminate();

        std::string RESOURCE_DIR;   /* Static resource directory */
        std::string APP_NAME;       /* Name of application */
        double timeStep;            /* Delta time */
        bool verbose;               /* Log things or not */

    private:
        double fps;                 /* Frames per second */
        double lastFpsTime;         /* Time at which last FPS was calculated */
        int nFrames;                /* Number of frames in current second */
        double lastFrameTime;       /* Time at which last frame was rendered */
        double runTime;             /* Global timer */

        Window windowHandler;       /* GLFW window */
        Loader loader;              /* Used to load in files and GPU memory */
};

#endif