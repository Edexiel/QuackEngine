void main()
{
    vec3 fragmentColor = vec3(0,0,0);

    vec3 normalMap = texture(material.normalMap, TexCoord).rgb;
    normalMap = normalize(TBN * (normalMap * 2.0 - 1.0));

    for (int i = 0 ; i < nbDirectionalLights ; i++)
    {
      fragmentColor += GetColorAfterDirectionalLight(directionalLights[i], vec3(Position), normalMap, TexCoord);
    }
    for (int i = 0 ; i < nbPointLights ; i++)
    {
      fragmentColor += GetColorAfterPointLight(pointLights[i], vec3(Position), normalMap, TexCoord);
    }
    for (int i = 0 ; i < nbSpotLights ; i++)
    {
      fragmentColor += GetColorAfterSpotLight(spotLights[i], vec3(Position), normalMap, TexCoord);
    }

    FragColor = GetColor(material, TexCoord) * vec4(fragmentColor, 1.f);
}