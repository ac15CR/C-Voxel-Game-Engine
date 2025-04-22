#version 460 core

in vec3 normal;
in vec2 tex_coord;
out vec4 frag_color;

uniform sampler2D tex;

layout(std140, binding = 1) uniform lights
{
    vec3 ambient;
    vec3 direction;
    vec3 direction_color;
};

void main()
{
    vec4 albedo = texture(tex, tex_coord);
    vec4 amb_color = vec4(ambient, 1.0) * albedo;

    vec3 light_dir = normalize(-direction);
    float diff = max(dot(normal, light_dir), 0.0);
    vec4 dir_color = vec4(diff * direction_color, 1.0) * albedo;

    frag_color = amb_color + dir_color;
}
