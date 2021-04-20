project(core)

add_library(
        ${PROJECT_NAME}
        STATIC

        libraries/imgui/imgui.h
        libraries/imgui/imgui.cpp
        libraries/imgui/imgui_internal.h
        libraries/imgui/imgui_draw.cpp
        libraries/imgui/imgui_tables.cpp
        libraries/imgui/imgui_widgets.cpp
        libraries/imgui/imstb_rectpack.h
        libraries/imgui/imstb_textedit.h
        libraries/imgui/imstb_truetype.h
        libraries/imgui/imgui_impl_glfw.h
        libraries/imgui/imgui_impl_glfw.cpp
        libraries/imgui/imgui_impl_opengl3.h
        libraries/imgui/imgui_impl_opengl3.cpp

        source/core/core.pch
        source/core/numerics/numbers.hpp
        source/core/numerics/bit_mask.cpp
        source/core/numerics/bit_mask.hpp
        source/core/numerics/vector2.hpp
        source/core/string/string.hpp
        source/core/collections/array.hpp
        source/core/collections/list.hpp
        source/core/collections/hash_map.hpp
        source/core/collections/hash_set.hpp
        source/core/entities/entity.hpp
        source/core/entities/entity_registry.hpp
        source/core/memory/unique_pointer.hpp
        source/core/memory/shared_pointer.hpp

        source/core/editor/camera_editor.cpp
        source/core/editor/camera_editor.hpp

        source/core/platform/window.hpp
        source/core/platform/glfw/glfw_window.cpp
        source/core/platform/glfw/glfw_window.hpp
        source/core/graphics/shader.cpp
        source/core/graphics/shader.hpp
        source/core/graphics/vertex_array.cpp
        source/core/graphics/vertex_array.hpp
        source/core/graphics/renderer.cpp
        source/core/graphics/renderer.hpp
        source/core/graphics/texture.cpp
        source/core/graphics/texture.hpp
        source/core/graphics/camera.cpp
        source/core/graphics/camera.hpp
        source/core/graphics/frame_buffer.cpp
        source/core/graphics/renderer_stats.hpp
        source/core/graphics/frame_buffer.hpp
        source/core/graphics/vertex_buffer.cpp
        source/core/graphics/vertex_buffer.hpp
        source/core/graphics/index_buffer.cpp
        source/core/graphics/index_buffer.hpp
        source/core/graphics/graphics.hpp
        source/core/graphics/graphics.cpp
        source/core/io/file_system.cpp
        source/core/io/file_system.hpp
        source/core/time/stopwatch.cpp
        source/core/time/stopwatch.hpp
        source/core/game/game.cpp
        source/core/game/game.hpp
        source/core/platform/input.hpp
        source/core/platform/glfw/glfw_input.cpp
        source/core/platform/glfw/glfw_input.hpp
        source/core/graphics/vertex_layout.cpp
        source/core/graphics/vertex_layout.hpp
        source/core/graphics/debug.hpp
        source/core/graphics/vertex_attribute.hpp
        source/core/game/components/sprite_component.hpp
        source/core/game/components/transform_component.hpp
        source/core/game/components/text_component.hpp
        source/core/game/components/transform_component.cpp
        source/core/game/systems/sprite_render_system.cpp
        source/core/game/systems/sprite_render_system.hpp
        source/core/game/systems/text_render_system.cpp
        source/core/game/systems/text_render_system.hpp
        source/core/algorithm/random.cpp
        source/core/algorithm/random.hpp
        source/core/numerics/rectangle.cpp
        source/core/numerics/rectangle.hpp
        source/core/math/math.cpp
        source/core/math/math.hpp
        source/core/graphics/vertex.hpp
        source/core/fonts/font.cpp
        source/core/fonts/font.hpp
        source/core/fonts/glyph.hpp
        source/core/fonts/font_builder.cpp
        source/core/fonts/font_builder.hpp
        source/core/fonts/character_range.hpp
        source/core/algorithm/algorithm.hpp
        source/core/string/codepoint.hpp
        source/core/ui/ui_element.cpp
        source/core/ui/ui_element.hpp
        source/core/ui/ui_root.cpp
        source/core/ui/ui_root.hpp
        source/core/ui/ui_image.cpp
        source/core/ui/ui_image.hpp
        source/core/game/components/ui_element_component.hpp
)

set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
add_subdirectory(${THIRD_PARTY_ROOT}/glfw glfw)
target_include_directories(${PROJECT_NAME} PRIVATE "${THIRD_PARTY_ROOT}/glfw/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

add_subdirectory(${THIRD_PARTY_ROOT}/utfcpp utfcpp)
target_include_directories(${PROJECT_NAME} PRIVATE "${THIRD_PARTY_ROOT}/utfcpp/source")

target_include_directories(${PROJECT_NAME} PUBLIC ${THIRD_PARTY_ROOT}/entt/single_include)

target_include_directories(${PROJECT_NAME} PUBLIC "${THIRD_PARTY_ROOT}/glm")

add_subdirectory(${THIRD_PARTY_ROOT}/stb_image stb_image)
target_include_directories(${PROJECT_NAME} PRIVATE "${THIRD_PARTY_ROOT}/stb_image/include")

add_subdirectory(${THIRD_PARTY_ROOT}/stb_truetype stb_truetype)
target_include_directories(${PROJECT_NAME} PRIVATE "${THIRD_PARTY_ROOT}/stb_truetype/include")

add_subdirectory(${THIRD_PARTY_ROOT}/glad glad)
target_include_directories(${PROJECT_NAME} PRIVATE "${THIRD_PARTY_ROOT}/glad/include")

add_subdirectory(${THIRD_PARTY_ROOT}/spdlog spdlog)
target_include_directories(${PROJECT_NAME} PRIVATE "${THIRD_PARTY_ROOT}/spdlog/include")

target_include_directories(${PROJECT_NAME} PRIVATE ${STEAMWORKS_INCLUDE_DIR})

target_precompile_headers(${PROJECT_NAME} PUBLIC source/core/core.pch)

target_link_libraries(${PROJECT_NAME} glad glfw stb_image stb_truetype spdlog utf8cpp ${STEAMWORKS_LIBRARY_LIB})
