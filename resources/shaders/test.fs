#version 100

precision mediump float;
#define M_PI 3.1415926535897932384626433832795

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform vec2 offset;
uniform vec2 size;
uniform vec2 windowSize;

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
	return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main()
{
    vec2 u_resolution = size;//vec2(400, 400);
    float offsetY = windowSize.y - size.y - offset.y;
    vec2 st = (gl_FragCoord.xy - vec2(offset.x, offsetY) )/u_resolution;

    // gl_FragColor = vec4(st, 0.0, 1.0);

    // float pct = 0.0;
    // pct = distance(st,vec2(0.5));
    // vec3 color = vec3(pct);
	// gl_FragColor = vec4( color, 1.0 );

    // float color = circle(st,0.9);
    // float color2 = circle(st,0.5);

    // if(color2 > 0.9)
	// gl_FragColor = vec4( 0.,1.,0., 1.-color2 );
    // else
	// gl_FragColor = vec4( 0.,1.,0., color );

    // vec2 delta = vec2(0.5, 0.5) - st;
    vec2 delta = st - vec2(0.5, 0.5);
    float angle = atan(delta.y, delta.x) + M_PI;

    float deg = angle * (180 / M_PI);

    if(deg > 90 && deg < 180)
    // gl_FragColor = vec4( 1.,1.,0., 1. );
        discard;
    else{

    // gl_FragColor = vec4( 0.,1.,0., 1. );


    // WORKING /////////////////////////////////
    float outerCircle = circle(st,0.9);
    float InnerCircle = circle(st,0.5);

	float outerCirclePaint = mix(0.0, 1.0, outerCircle);
	float innerCirclePaint = mix(outerCirclePaint, 0.0, InnerCircle);

    if(deg < 90 || deg > 350)
        gl_FragColor = vec4( 0.,1.,0., innerCirclePaint );
    else
        gl_FragColor = vec4( 1.,1.,0., innerCirclePaint );
    // WORKING /////////////////////////////////
    }

}
