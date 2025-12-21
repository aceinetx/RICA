
#version 330

in vec2 fragTexCoord;    

uniform sampler2D textureSampler; 
uniform vec2 resolution;          
uniform float time;              

out vec4 finalColor;



vec2 BarrelDistortion(vec2 uv) {
    vec2 center = uv - 0.5; 
    
    float dist = dot(center, center);
    
    float K = 0.01; 
    
    return (uv + center * K * dist);
}

float ScanLines(vec2 uv) {
    float line = uv.y * resolution.y;
    
    float effect = 0.8 + 0.2 * cos(line * 2.14159 * 2.0); // Мягкие линии
    
    
    return effect;
}

float Vignette(vec2 uv) {
    vec2 pos = (uv - 0.5) * 2.0; 
    
    float dist = dot(pos, pos);
    
    float K = 0.6; 
    return 1.0 - dist * K; 
}



void main() {
    vec2 uv = fragTexCoord;

    uv = BarrelDistortion(uv);

    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0); 
        return;
    }

    vec4 color = texture(textureSampler, uv);

    float scanline_multiplier = ScanLines(uv);
    color.rgb *= scanline_multiplier;

    float vignette_multiplier = Vignette(uv);
    color.rgb *= vignette_multiplier;
    
    finalColor = color;
}