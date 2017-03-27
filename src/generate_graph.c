#include <stdio.h>

typedef enum region {
  ALASKA = 0, NORTHWEST_TERRITORY, GREENLAND, ALBERTA, 
  ONTARIO, QUEBEC, WESTERN_UNITED_STATES, 
  EASTERN_UNITED_STATES, CENTRAL_AMERICA, // NORTH AMERICA (9)
  ICELAND, SCANDINAVIA, UKRAINE, GREAT_BRITAIN, 
  NORTHERN_EUROPE, WESTERN_EUROPE, SOUTHERN_EUROPE, // EUROPE (7)
  URAL, SIBERIA, YAKUTSK, KAMCHATKA, IRKUTSK, MONGOLIA, 
  JAPAN, AFGHANISTAN, CHINA, MIDDLE_EAST, INDIA, SIAM, // ASIA (12)
  VENEZUELA, PERU, BRAZIL, ARGENTINA, // SOUTH AMERICA (4)
  NORTH_AFRICA, EGYPT, CONGO, EAST_AFRICA, SOUTH_AFRICA, MADAGASCAR, // AFRICA (6)
  INDONESIA, NEW_GUINEA, WESTERN_AUSTRALIA, EASTERN_AUSTRALIA // OCEANA (4)
} region_t;

char *REGION_NAME[42] = {
  "ALASKA", "NORTHWEST_TERRITORY", "GREENLAND", "ALBERTA",
  "ONTARIO", "QUEBEC", "WESTERN_UNITED_STATES",
  "EASTERN_UNITED_STATES", "CENTRAL_AMERICA", "ICELAND",
  "SCANDINAVIA", "UKRAINE", "GREAT_BRITAIN",
  "NORTHERN_EUROPE", "WESTERN_EUROPE", "SOUTHERN_EUROPE",
  "URAL", "SIBERIA", "YAKUTSK", "KAMCHATKA",
  "IRKUTSK", "MONGOLIA", "JAPAN", "AFGHANISTAN",
  "CHINA", "MIDDLE_EAST", "INDIA", "SIAM",
  "VENEZUELA", "PERU", "BRAZIL", "ARGENTINA",
  "NORTH_AFRICA", "EGYPT", "CONGO", "EAST_AFRICA",
  "SOUTH_AFRICA", "MADAGASCAR", "INDONESIA",
  "NEW_GUINEA", "WESTERN_AUSTRALIA", "EASTERN_AUSTRALIA"
};

char BOARD[42][42] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //ALASKA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //NORTHWEST_TERRITORY
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //GREENLAND
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //ALBERTA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //ONTARIO
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //QUEBEC
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //WESTERN_UNITED_STATES
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //EASTERN_UNITED_STATES
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //CENTRAL_AMERICA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //ICELAND
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //SCANDINAVIA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //UKRAINE
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //GREAT_BRITAIN
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //NORTHERN_EUROPE
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //WESTERN_EUROPE
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //SOUTHERN_EUROPE
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //URAL
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //SIBERIA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //YAKUTSK
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //KAMCHATKA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //IRKUTSK
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //MONGOLIA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //JAPAN
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //AFGHANISTAN
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //CHINA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //MIDDLE_EAST
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //INDIA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //SIAM
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //VENEZUELA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //PERU
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //BRAZIL
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //ARGENTINA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //NORTH_AFRICA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //EGYPT
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //CONGO
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //EAST_AFRICA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //SOUTH_AFRICA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //MADAGASCAR
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //INDONESIA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //NEW_GUINEA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //WESTERN_AUSTRALIA
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}, //EASTERN_AUSTRALIA
};

void set(region_t src, region_t regions[], int size) {
  int i;
  for(i = 0; i < size; i++) { BOARD[src][regions[i]] = 1; }
}

int main() {

  region_t alaska_regions[] = { NORTHWEST_TERRITORY, ALBERTA, KAMCHATKA };
  set(ALASKA, alaska_regions, 3);

  region_t nw_regions[] = { ALASKA, ALBERTA, ONTARIO, GREENLAND };
  set(NORTHWEST_TERRITORY, nw_regions, 4);

  region_t green_regions[] = { QUEBEC, ONTARIO, NORTHWEST_TERRITORY, ICELAND };
  set(GREENLAND, green_regions, 4);

  region_t alb_regions[] = { ALASKA, NORTHWEST_TERRITORY, ONTARIO, WESTERN_UNITED_STATES };
  set(ALBERTA, alb_regions, 4);

  region_t ont_regions[] = { ALBERTA, NORTHWEST_TERRITORY, GREENLAND, QUEBEC, WESTERN_UNITED_STATES, EASTERN_UNITED_STATES };
  set(ONTARIO, ont_regions, 6);

  region_t que_regions[] = { ONTARIO, GREENLAND, EASTERN_UNITED_STATES };
  set(QUEBEC, que_regions, 3);

  region_t wus_regions[] = { ALBERTA, ONTARIO, EASTERN_UNITED_STATES, CENTRAL_AMERICA };
  set(WESTERN_UNITED_STATES, wus_regions, 4);

  region_t eus_regions[] = { WESTERN_UNITED_STATES, ONTARIO, QUEBEC, CENTRAL_AMERICA };
  set(EASTERN_UNITED_STATES, eus_regions, 4);

  region_t ca_regions[] = { WESTERN_UNITED_STATES, EASTERN_UNITED_STATES, VENEZUELA };
  set(CENTRAL_AMERICA, ca_regions, 3);

  region_t ice_regions[] = { GREENLAND, GREAT_BRITAIN, SCANDINAVIA };
  set(ICELAND, ice_regions, 3);

  region_t scan_regions[] = { ICELAND, GREAT_BRITAIN, NORTHERN_EUROPE, UKRAINE };
  set(SCANDINAVIA, scan_regions, 4);

  region_t uk_regions[] = { SCANDINAVIA, NORTHERN_EUROPE, SOUTHERN_EUROPE, URAL, MIDDLE_EAST, AFGHANISTAN };
  set(UKRAINE, uk_regions, 6);

  region_t brit_regions[] = { ICELAND, WESTERN_EUROPE, SCANDINAVIA, NORTHERN_EUROPE };
  set(GREAT_BRITAIN, brit_regions, 4);

  region_t neu_regions[] = { WESTERN_EUROPE, SOUTHERN_EUROPE, UKRAINE, GREAT_BRITAIN, SCANDINAVIA  };
  set(NORTHERN_EUROPE, neu_regions, 5);

  region_t weu_regions[] = { GREAT_BRITAIN, NORTHERN_EUROPE, SOUTHERN_EUROPE, NORTH_AFRICA };
  set(WESTERN_EUROPE, weu_regions, 4);

  region_t seu_regions[] = { WESTERN_EUROPE, NORTHERN_EUROPE, UKRAINE, MIDDLE_EAST, EGYPT, NORTH_AFRICA };
  set(SOUTHERN_EUROPE, seu_regions, 6);

  region_t ural_regions[] = { UKRAINE, SIBERIA, CHINA, AFGHANISTAN };
  set(URAL, ural_regions, 4);

  region_t sib_regions[] = { URAL, YAKUTSK, IRKUTSK, MONGOLIA, CHINA };
  set(SIBERIA, sib_regions, 5);

  region_t yak_regions[] = { SIBERIA, KAMCHATKA, IRKUTSK };
  set(YAKUTSK, yak_regions, 3);

  region_t kam_regions[] = { YAKUTSK, IRKUTSK, MONGOLIA, JAPAN, ALASKA };
  set(KAMCHATKA, kam_regions, 5);

  region_t irk_regions[] = { SIBERIA, YAKUTSK, KAMCHATKA, MONGOLIA };
  set(IRKUTSK, irk_regions, 4); 

  region_t mon_regions[] = { SIBERIA, IRKUTSK, KAMCHATKA, JAPAN, CHINA };
  set(MONGOLIA, mon_regions, 5);

  region_t jap_regions[] = { KAMCHATKA, MONGOLIA };
  set(JAPAN, jap_regions, 2);

  region_t afghan_regions[] = { URAL, CHINA, INDIA, MIDDLE_EAST, UKRAINE };
  set(AFGHANISTAN, afghan_regions, 5);

  region_t china_regions[] = { SIAM, INDIA, AFGHANISTAN, URAL, SIBERIA, MONGOLIA };
  set(CHINA, china_regions, 6);

  region_t mide_regions[] = { SOUTHERN_EUROPE, UKRAINE, AFGHANISTAN, INDIA, EGYPT, EAST_AFRICA };
  set(MIDDLE_EAST, mide_regions, 6);

  region_t ind_regions[] = { MIDDLE_EAST, AFGHANISTAN, CHINA, SIAM };
  set(INDIA, ind_regions, 4);

  region_t sia_regions[] = { INDIA, CHINA, INDONESIA };
  set(SIAM, sia_regions, 3);

  region_t ven_regions[] = { CENTRAL_AMERICA, PERU, BRAZIL };
  set(VENEZUELA, ven_regions, 3);

  region_t peru_regions[] = { VENEZUELA, BRAZIL, ARGENTINA };
  set(PERU, peru_regions, 3);

  region_t brazil_regions[] = { VENEZUELA, PERU, ARGENTINA, NORTH_AFRICA };
  set(BRAZIL, brazil_regions, 4);

  region_t arg_regions[] = { PERU, BRAZIL };
  set(ARGENTINA, arg_regions, 2);

  region_t na_regions[] = { BRAZIL, WESTERN_EUROPE, SOUTHERN_EUROPE, EGYPT, EAST_AFRICA, CONGO };
  set(NORTH_AFRICA, na_regions, 6);

  region_t eg_regions[] = { NORTH_AFRICA, SOUTHERN_EUROPE, MIDDLE_EAST, EAST_AFRICA };
  set(EGYPT, eg_regions, 4);

  region_t co_regions[] = { NORTH_AFRICA, EAST_AFRICA, SOUTH_AFRICA };
  set(CONGO, co_regions, 3);

  region_t ea_regions[] = { EGYPT, NORTH_AFRICA, CONGO, SOUTH_AFRICA, MADAGASCAR, MIDDLE_EAST };
  set(EAST_AFRICA, ea_regions, 6);

  region_t sa_regions[] = { CONGO, EAST_AFRICA, MADAGASCAR };
  set(SOUTH_AFRICA, sa_regions, 3);

  region_t ma_regions[] = { SOUTH_AFRICA, EAST_AFRICA };
  set(MADAGASCAR, ma_regions, 2);

  region_t in_regions[] = { SIAM, NEW_GUINEA, WESTERN_AUSTRALIA };
  set(INDONESIA, in_regions, 3);

  region_t ng_regions[] = { INDONESIA, EASTERN_AUSTRALIA };
  set(NEW_GUINEA, ng_regions, 2);

  region_t wa_regions[] = { INDONESIA, EASTERN_AUSTRALIA };
  set(WESTERN_AUSTRALIA, wa_regions, 2);

  region_t eaa_regions[] = { WESTERN_AUSTRALIA, NEW_GUINEA };
  set(EASTERN_AUSTRALIA, eaa_regions, 2);

  printf("bool BOARD[42][42] = {\n");
  int i, j;
  for(i = 0; i < 42; i++) {
    printf("\t{");
    for(j = 0; j < 42; j++) {
       printf("%d", BOARD[i][j]);
       if(j < 41) { printf(","); }
    }
    printf("} // %s\n", REGION_NAME[i]);
  }
  printf("};\n");

  printf("ADJACENCIES:\n");
  for(i = 0; i < 42; i++) {
    printf("%s:: %d --> ", REGION_NAME[i], i);
    for(j = 0; j < 42; j++) {
      if(BOARD[i][j]) { printf("%s, ", REGION_NAME[j]); }  
    }
    printf("\n");
  }

  return 0;
}
