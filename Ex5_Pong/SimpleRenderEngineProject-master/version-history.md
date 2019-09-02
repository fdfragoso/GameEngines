## Version history

 * 0.9.11 Improved sprite-atlas support + documentation
 * 0.9.10 Improved Linux support
 * 0.9.9 Minor Bugfixes
 * 0.9.8 Update ImGUI and GLM
 * 0.9.7 Add Mesh preview and Shader preview in profiler
 * 0.9.6 Offset in shaders for calculating depth values
 * 0.9.5 Profiling 
 * 0.9.4 High DPI, Fullscreen mode, mouse cursor visibility and mouse lock. 
 * 0.9.3 Log. 
 * 0.9.2 Sprite rendering. 
 * 0.9.1 Multiple materials per draw call and multiple index-sets. ModelImporter (Obj). 
 * 0.9.0 Framebuffer objects. RenderPass::readPixels(). Simplified Camera projection. RenderPass::create() (More consistent use of builder pattern)
 * 0.8.0 Resource memory management using shared_ptr. Materials created by Shader.createMaterial().
 * 0.7.1 sRGB. Improve MSVC improvement. Improve builder pattern.
 * 0.7.0 Add SDLRenderer. Custom mesh attributes. Simplify Camera::setPerspectiveProjection.
 * 0.6.0 Add Material and RenderPass. Improve ImGUI integration. 
 * 0.5.3 Rename namespace and folders from SRE to sre 
 * 0.5.2 Add mesh bounds 
 * 0.5.1 Clean up documentation and minor API updates. 
 * 0.5.0 Rename SimpleRenderEngine class to Renderer. Add cube map support. 
 * 0.4.1 Add RenderStats
 * 0.4.0 Merged Mesh and ParticleMesh into the Mesh class
 * 0.3.1 Creation of Light, Sphere(Mesh), Cube(Mesh) and Quad(Mesh) using Builder pattern.
 * 0.3.0 Creation of Texture, Mesh and Shader using Builder pattern.
 * 0.2.9 Fixed issues with specular highlight
 * 0.2.8 Added Emscripten support
 * 0.2.7 Add more mesh topologies (line strip, triangle strip and triangle fans). Add Debug::drawLineStrip(). 
 * 0.2.6 Fix point-light attenuation 
 * 0.2.5 Set Camera default viewport
 * 0.2.4 Restructured include folder and CMake build. Fix particle bug.
 * 0.2.2 ParticleMesh Support for OpenGL 3.1
 * 0.2.1 Make particle size depend on viewport. Move internal headers into impl.  
 * 0.2 Move specularity from Light to a normal shader uniform (since logically it belongs to material instead of the light source)  
   - Add ParticleMesh 
   - Add support for imgui 
   - Remove simple text rendering
   - Refactoring Shader: verify uniform names and types.
 * 0.1 Initial version