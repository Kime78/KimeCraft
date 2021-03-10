#version 330 core

in vec3 Normal;
in vec3 Color;
in vec3 FragPos;

out vec4 outColor;

uniform vec3 light_pos;
uniform vec3 viewPos;

void main()
{ 
    float ambient_strength = 0.0;
    vec3 ambient = ambient_strength * vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(light_pos - FragPos);

    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
    
    float specular_strenght = 0.5;
    vec3 view_dir = normalize(viewPos - FragPos);
    vec3 reflect_dir = reflect(-light_dir, norm); 
    
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 2);
    vec3 specular = specular_strenght * spec * vec3(1.0, 1.0, 1.0); 

    vec3 result = (diffuse + ambient + specular) * Color;
    outColor = vec4(result, 1.0);
}