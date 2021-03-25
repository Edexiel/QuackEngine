void main()
{
    vec3 fragmentColor = vec3(0,0,0);

    for (int i = 0 ; i < NB_DIRECTIONAL_LIGHT ; i++)
    {
      fragmentColor += GetColorAfterDirectionalLight(directionalLights[i], vec3(Position), normalize(vec3(Normal)), TexCoord);
    }
    for (int i = 0 ; i < NB_POINT_LIGHT ; i++)
    {
      fragmentColor += GetColorAfterPointLight(pointLights[i], vec3(Position), normalize(vec3(Normal)), TexCoord);
    }
    for (int i = 0 ; i < NB_SPOT_LIGHT ; i++)
    {
      fragmentColor += GetColorAfterSpotLight(spotLights[i], vec3(Position), normalize(vec3(Normal)), TexCoord);
    }

    FragColor = GetColor(material, TexCoord) * vec4(fragmentColor, 1.f);
}