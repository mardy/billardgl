void LSupdateGL();
void LSidle();

extern GLint AktuellesFenster, KugelAufloesung,
  Texturgroesse, TischTexturgroesse, AmbientesLicht, 
  TischLampen, GrueneLampe, Reflektionen, 
  AnzeigeTexturgroesse, Spiel,
  LadeFortschritt;

extern class Kugel Kugel[16];
extern class Anzeige Anzeige;
extern class Menu Menu;
extern class Schiedsrichter Schiedsrichter;
extern class Beleuchtung Beleuchtung;
extern GLuint dreizehntextur;
extern GLuint logotextur;
