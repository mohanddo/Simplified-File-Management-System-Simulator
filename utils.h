#ifndef UTILS_H
#define UTILS_H

void printAllocationTable(FILE *ms);
int seekToFirstBloc(FILE *ms);
void readMsMetaDonnees(FILE *ms, MsMetaDonnees *msMetaDonnees);
void seekToMetaDonneesBloc(FILE *ms);
void printMetaDonnees(MetaDonnees meta);
void printMetaDonneesBloc(FILE *ms);
void readMetaDonneesBloc(FILE *ms, MetaDonneesBloc *metaDonneesBloc);
void printMainBlocs(FILE *ms);

#endif