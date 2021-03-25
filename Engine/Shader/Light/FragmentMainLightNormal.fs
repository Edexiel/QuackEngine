void main()
{
    vec3 fragmentColor = vec3(0,0,0);

    vec3 normalMap = texture(material.normalMap, TexCoord).rgb;
    normalMap = normalize(TBN * (normalMap * 2.0 - 1.0));

    for (int i = 0 ; i < NB_DIRECTIONAL_LIGHT ; i++)
    {
      fragmentColor += GetColorAfterDirectionalLight(directionalLights[i], vec3(Position), normalize(vec3(normalMap)), TexCoord);
    }
    for (int i = 0 ; i < NB_POINT_LIGHT ; i++)
    {
      fragmentColor += GetColorAfterPointLight(pointLights[i], vec3(Position), normalize(vec3(normalMap)), TexCoord);
    }
    for (int i = 0 ; i < NB_SPOT_LIGHT ; i++)
    {
      fragmentColor += GetColorAfterSpotLight(spotLights[i], vec3(Position), normalize(vec3(normalMap)), TexCoord);
    }

    FragColor = GetColor(material, TexCoord) * vec4(fragmentColor, 1.f);
}