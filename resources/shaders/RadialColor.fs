#version 100

precision mediump float;
#define M_PI 3.1415926535897932384626433832795

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform vec2 u_glPosition;
uniform float u_size;
uniform float u_value;
uniform sampler2D u_texture;

float rotateAngle(float value, float angle) {
    if(value > angle)
        return value - angle;
    else
        return value + (360. - angle);
}

void main()
{
    vec2 st = (gl_FragCoord.xy - u_glPosition )/ vec2(u_size, u_size);

    // Calculate angle in degrees
    vec2 delta = st - vec2(0.5, 0.5);
    float angle = atan(delta.y, delta.x) + M_PI;
    float deg = angle * (180. / M_PI);

    // Flip direction
    deg = 360. - deg;

    // Rotate reference angle
    deg = rotateAngle(deg, 270.);

    if(deg > 270.)
        discard;
    else{

        vec4 texCol = texture2D(u_texture, st);

        if(deg > u_value)
            gl_FragColor = vec4( 0.506, 0.486, 0.514, texCol.a );
        else
            gl_FragColor = vec4( 0.992, 0.565, 0.071, texCol.a );

    }

}
