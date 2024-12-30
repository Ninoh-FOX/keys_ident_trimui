#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Inicialización de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Verificar si hay gamepads conectados
    int numJoysticks = SDL_NumJoysticks();
    if (numJoysticks == 0) {
        printf("No gamepads connected.\n");
    } else {
        printf("Gamepad detected.\n");
    }

    // Abrir el primer gamepad si está conectado
    SDL_GameController *controller = NULL;
    if (numJoysticks > 0) {
        controller = SDL_GameControllerOpen(0);
        if (controller == NULL) {
            fprintf(stderr, "Error opening gamepad: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
    }

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            // Eventos de teclado (teclas físicas)
            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode key = event.key.keysym.sym;
                printf("Key pressed: %s (SDL_Keycode: %d)\n", SDL_GetKeyName(key), key);
            }

            // Eventos de teclas liberadas
            if (event.type == SDL_KEYUP) {
                SDL_Keycode key = event.key.keysym.sym;
                printf("Key released: %s (SDL_Keycode: %d)\n", SDL_GetKeyName(key), key);
            }

            // Eventos de joystick/gamepad (botones presionados)
            if (event.type == SDL_CONTROLLERBUTTONDOWN) {
                SDL_GameControllerButton button = event.cbutton.button;
                printf("Button pressed on gamepad: %s (Button code: %d)\n", SDL_GameControllerGetStringForButton(button), button);
            }

            // Eventos de joystick/gamepad (botones liberados)
            if (event.type == SDL_CONTROLLERBUTTONUP) {
                SDL_GameControllerButton button = event.cbutton.button;
                printf("Button released on gamepad: %s (Button code: %d)\n", SDL_GameControllerGetStringForButton(button), button);
            }

            // Eventos de movimiento de los ejes del joystick (eje X y Y)
            if (event.type == SDL_CONTROLLERAXISMOTION) {
                SDL_GameControllerAxis axis = event.caxis.axis;
                printf("Axis motion on gamepad: %s (Axis code: %d) Value: %d\n", SDL_GameControllerGetStringForAxis(axis), axis, event.caxis.value);
            }
        }
    }

    // Cerrar el gamepad si estaba abierto
    if (controller) {
        SDL_GameControllerClose(controller);
    }

    SDL_Quit();
    return 0;
}
