#include "Master.h"

int main()
{
    const Vector2 screenSize{1280, 720};

    InitWindow(screenSize.x, screenSize.y, "CarProjectRaylib");
    SetTargetFPS(60);

    Camera camera = {0};
    camera.position = Vector3{6.0f, 6.0f, 6.0f}; // Camera position
    camera.target = Vector3{0.0f, 2.0f, 0.0f};   // Camera looking at point
    camera.up = Vector3{0.0f, 1.0f, 0.0f};       // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                         // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera projection type

    Model carModel = LoadModel("C:/Users/break/Downloads/mini_cooper_gp_r56.glb");
    std::cout << "Car bones: " << carModel.bones << std::endl;
    std::cout << "Car boneCount: " << carModel.boneCount << std::endl;
    std::cout << "Car matCount: " << carModel.materialCount << std::endl;
    std::cout << "Car mats: " << carModel.materials << std::endl;
    std::cout << "Car meshCount: " << carModel.meshCount << std::endl;
    std::cout << "Car meshes: " << carModel.meshes << std::endl;
    std::cout << "Car meshMat: " << carModel.meshMaterial << std::endl;

    Vector3 modelPosition = {11.0f, 0.0f, 11.0f};

    struct Anim
    {
        int animsCount = 0;
        unsigned int animIndex = 0;
        unsigned int animCurrentFrame = 0;
        ModelAnimation *modelAnimations = LoadModelAnimations("C:/Users/break/Downloads/mini_cooper_gp_r56.glb", &animsCount);
    };

    while (!WindowShouldClose())
    {
        HideCursor();
        UpdateCamera(&camera, CAMERA_FREE);
        DisableCursor();
        // Anim anim;
        // if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        //     anim.animIndex = (anim.animIndex + 1) % anim.animsCount;
        // else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        //     anim.animIndex = (anim.animIndex + anim.animsCount - 1) % anim.animsCount;
        //
        // ModelAnimation animation = anim.modelAnimations[anim.animIndex];
        // anim.animCurrentFrame = (anim.animCurrentFrame + 1) % animation.frameCount;
        // UpdateModelAnimation(carModel, animation, anim.animCurrentFrame);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Use the LEFT/RIGHT mouse buttons to switch animation", 10, 10, 20, GRAY);
        // DrawText(TextFormat("Animation: %s", animation.name), 10, GetScreenHeight() - 20, 10, DARKGRAY);

        BeginMode3D(camera);
        BoundingBox carBoundingBox = GetModelBoundingBox(carModel);
        DrawModel(carModel, modelPosition, 1.0f, WHITE);
        DrawBoundingBox(carBoundingBox, RED);
        DrawGrid(100, 1.0f);

        EndMode3D();

        EndDrawing();
    }
    UnloadModel(carModel);
    CloseWindow();
}

/*
INFO: VAO: [ID 16] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 17] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 18] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 19] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 20] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 21] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 22] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 23] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 24] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 25] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 26] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 27] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 28] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 29] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 30] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 31] Mesh uploaded successfully to VRAM (GPU)
INFO: FILEIO: [C:/dev/CPP/CarProjectRaylib/models/MiniCooper.glb] File loaded successfully
INFO: MODEL: [C:/dev/CPP/CarProjectRaylib/models/MiniCooper.glb] Loaded animation: doors.open.close (197 frames, 3.333333s)
INFO: MODEL: [C:/dev/CPP/CarProjectRaylib/models/MiniCooper.glb] Loaded animation: Armature.001Action.001 (1 frames, 0.000000s)
INFO: MODEL: [C:/dev/CPP/CarProjectRaylib/models/MiniCooper.glb] Loaded animation: Armature.002Action (1 frames, 0.000000s)
INFO: MODEL: [C:/dev/CPP/CarProjectRaylib/models/MiniCooper.glb] Loaded animation: Cab_Uni_Body.002Action (1 frames, 0.000000s)
WARNING: MODEL: [C:/dev/CPP/CarProjectRaylib/models/MiniCooper.glb] expected exactly one skin to load animation data from, but found 3
*/

/*INFO: Initializing raylib 5.5
INFO: Platform backend: DESKTOP (GLFW)
INFO: Supported raylib modules:
INFO:     > rcore:..... loaded (mandatory)
INFO:     > rlgl:...... loaded (mandatory)
INFO:     > rshapes:... loaded (optional)
INFO:     > rtextures:. loaded (optional)
INFO:     > rtext:..... loaded (optional)
INFO:     > rmodels:... loaded (optional)
INFO:     > raudio:.... loaded (optional)
INFO: DISPLAY: Device initialized successfully
INFO:     > Display size: 1920 x 1080
INFO:     > Screen size:  1280 x 720
INFO:     > Render size:  1280 x 720
INFO:     > Viewport offsets: 0, 0
INFO: GLAD: OpenGL extensions loaded successfully
INFO: GL: Supported extensions count: 403
INFO: GL: OpenGL device information:
INFO:     > Vendor:   NVIDIA Corporation
INFO:     > Renderer: NVIDIA GeForce RTX 4060 Ti/PCIe/SSE2
INFO:     > Version:  3.3.0 NVIDIA 572.60
INFO:     > GLSL:     3.30 NVIDIA via Cg compiler
INFO: GL: VAO extension detected, VAO functions loaded successfully
INFO: GL: NPOT textures extension detected, full NPOT textures supported
INFO: GL: DXT compressed textures supported
INFO: GL: ETC2/EAC compressed textures supported
INFO: PLATFORM: DESKTOP (GLFW - Win32): Initialized successfully
INFO: TEXTURE: [ID 1] Texture loaded successfully (1x1 | R8G8B8A8 | 1 mipmaps)
INFO: TEXTURE: [ID 1] Default texture loaded successfully
INFO: SHADER: [ID 1] Vertex shader compiled successfully
INFO: SHADER: [ID 2] Fragment shader compiled successfully
INFO: SHADER: [ID 3] Program shader loaded successfully
INFO: SHADER: [ID 3] Default shader loaded successfully
INFO: RLGL: Render batch vertex buffers loaded successfully in RAM (CPU)
INFO: RLGL: Render batch vertex buffers loaded successfully in VRAM (GPU)
INFO: RLGL: Default OpenGL state initialized successfully
INFO: TEXTURE: [ID 2] Texture loaded successfully (128x128 | GRAY_ALPHA | 1 mipmaps)
INFO: FONT: Default font loaded successfully (224 glyphs)
INFO: SYSTEM: Working Directory: C:\dev\CPP\CarProjectRaylib\build
INFO: TIMER: Target time per frame: 16.667 milliseconds
INFO: FILEIO: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] File loaded successfully
INFO: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Model basic data (glb) loaded successfully
INFO:     > Meshes count: 15
INFO:     > Materials count: 15 (+1 default)
INFO: IMAGE: Data loaded successfully (4096x4096 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 3] Texture loaded successfully (4096x4096 | R8G8B8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (1024x1024 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 4] Texture loaded successfully (1024x1024 | R8G8B8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (256x256 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 5] Texture loaded successfully (256x256 | R8G8B8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (4096x4096 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 6] Texture loaded successfully (4096x4096 | R8G8B8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (256x256 | R8G8B8A8 | 1 mipmaps)
INFO: TEXTURE: [ID 7] Texture loaded successfully (256x256 | R8G8B8A8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (128x128 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 8] Texture loaded successfully (128x128 | R8G8B8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (512x512 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 9] Texture loaded successfully (512x512 | R8G8B8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (512x512 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 10] Texture loaded successfully (512x512 | R8G8B8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (512x512 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 11] Texture loaded successfully (512x512 | R8G8B8 | 1 mipmaps)
INFO: IMAGE: Data loaded successfully (512x512 | R8G8B8 | 1 mipmaps)
INFO: TEXTURE: [ID 12] Texture loaded successfully (512x512 | R8G8B8 | 1 mipmaps)
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
WARNING: MODEL: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] Indices data converted from u32 to u16, possible loss of data
INFO: VAO: [ID 2] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 3] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 4] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 5] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 6] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 7] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 8] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 9] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 10] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 11] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 12] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 13] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 14] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 15] Mesh uploaded successfully to VRAM (GPU)
INFO: VAO: [ID 16] Mesh uploaded successfully to VRAM (GPU)
INFO: FILEIO: [C:/Users/break/Downloads/mini_cooper_gp_r56.glb] File loaded successfully*/