#ifndef VOO_H
#define VOO_H

/* Definição da estrutura do Voo, que apresenta todos os dados relativos a cada voo, 
sendo ainda acrescentado o número total de passageiros, de cada voo, e o respetivo delay. */
typedef struct Voo Voo;

Voo *createVoo(char *id, char *airline, char *plane_model, char *total_seats, char *origin, char *destination, char *schedule_departure_date, char *schedule_arrival_date, char *real_departure_date, char *real_arrival_date, char *pilot, char *copilot, char *notes, int delay);

void freeVoo(Voo *voo);

char *vooGetId(Voo *voo);

char *vooGetAirline(Voo *voo);

char *vooGetPlaneModel(Voo *voo);

char *vooGetTotalSeats(Voo *voo);

char *vooGetOrigin(Voo *voo);

char *vooGetDestination(Voo *voo);

char *vooGetScheduleDepartureDate(Voo *voo);

char *vooGetScheduleArrivalDate(Voo *voo);

char *vooGetRealDepartureDate(Voo *voo);

char *vooGetRealArrivalDate(Voo *voo);

char *vooGetPilot(Voo *voo);

char *vooGetCopilot(Voo *voo);

char *vooGetNotes(Voo *voo);

int vooGetTotalPassengers(Voo *voo);

int vooGetDelay(Voo *voo);

Voo *vooGetNext(Voo *voo);

void setNextVoo(struct Voo *voo, struct Voo *next_voo);


#endif

