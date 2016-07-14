#version 150
#define RING_PROGRESSIVE
//#define RING_MODULO
//#define RING_SINE
//#define RING_FRACT

in vec3 vecNormal;
in vec4 vecPosition;
in vec2 st;

out vec4 fragColor;

// this are set in the OF app
uniform vec3 uLightPosition;
uniform vec4 uMaterialColor;
uniform float uTime;
uniform float uThickness;
uniform float uScale;

// http://www.iquilezles.org/www/articles/functions/functions.htm
float cubicPulse( float c, float w, float x ){
    x = abs(x - c);
    if( x>w ) return 0.0;
    x /= w;
    return 1.0 - x*x*(3.0-2.0*x);
}

float plot(vec2 st, float pct){
    return  smoothstep( pct-0.052, pct, st.y) -
    smoothstep( pct, pct+0.02, st.y);
}

float nRing = 6.0;

void main(){
    // basic lambertian lighting
    // not used in this shaders
    vec3 lightDirection = normalize(vecPosition.xyz - uLightPosition);
    float dProd = max(0.3, dot(vecNormal, lightDirection));

    //color
    vec4 color = uMaterialColor;
    #ifdef RING_PROGRESSIVE
        for(int i = 1; i<= nRing; i++){
            color += vec4(vec3(
                               cubicPulse(abs(sin(uTime)),uThickness,st.y/i)
                          ), 1.0);
        }
    #endif

    #ifdef RING_MODULO
        //programmatically
//        float inc = 1.0/nRing;
//        float padding = 0.0;
//        for(int i = 1; i<= nRing; i++){
//            color += vec4(vec3(
//                               cubicPulse(mod(uTime*uScale, 1.0),uThickness,(st.y+padding))
//                          ), 1.0);
//            padding+=inc;
//        }
        float y = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y);
        float y1 = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y+0.2);
        float y2 = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y-0.2);
        float y3 = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y+0.4);
        float y4 = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y-0.4);
        float y5 = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y+0.6);
        float y6 = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y-0.6);
        float y7 = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y+0.8);
        float y8 = cubicPulse(mod(uTime*uScale, 1.0),uThickness,st.y-0.8);
        color += vec4(vec3(y), 1.0);
        color += vec4(vec3(y1), 1.0);
        color += vec4(vec3(y2), 1.0);
        color += vec4(vec3(y3), 1.0);
        color += vec4(vec3(y4), 1.0);
        color += vec4(vec3(y5), 1.0);
        color += vec4(vec3(y6), 1.0);
        color += vec4(vec3(y7), 1.0);
        color += vec4(vec3(y8), 1.0);
    #endif

    #ifdef RING_SINE
        float y = cubicPulse(abs(sin(uTime*uScale)),uThickness,st.y);
        float y1 = cubicPulse(abs(sin(uTime*uScale)),uThickness,st.y+0.2);
        float y2 = cubicPulse(abs(sin(uTime*uScale)),uThickness,st.y+0.4);
        float y3 = cubicPulse(abs(sin(uTime*uScale)),uThickness,st.y+0.6);
        float y4 = cubicPulse(abs(sin(uTime*uScale)),uThickness,st.y+0.8);
        color += vec4(vec3(y), 1.0);
        color += vec4(vec3(y1), 1.0);
        color += vec4(vec3(y2), 1.0);
        color += vec4(vec3(y3), 1.0);
        color += vec4(vec3(y4), 1.0);
    #endif

    vec4 col = vec4( vec3( dProd ) * vec3( color ), 1.0 );
    //vec4 col = vec4( vec3( color ), 1.0 );
    fragColor = col;
}