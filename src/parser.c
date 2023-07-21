#include <stdio.h>

#include "auxiliary_modules.h"

int parser_counter(FILE *fp, s21_object *object) {
  char line[256];
  while (fgets(line, sizeof(line), fp)) {
    if (line[0] != '\n' && line[0] != '#') {
      char token[3];
      if (sscanf(line, "%2s", token) == 1) {
        if (strcmp(token, "f") == 0) {
          object->num_of_polygons += 1;
        } else if (strcmp(token, "v") == 0) {
          object->num_of_vertices += 1;
        }
      }
    }
  }
  return object->num_of_vertices;
}

void object_parser(FILE *fp, s21_object *object, s21_vertex *vertex,
                   int num_of_vert) {
  setlocale(LC_NUMERIC, "C");
  vertex = (s21_vertex *)malloc(num_of_vert * sizeof(s21_vertex));
  object->polygons = malloc(object->num_of_polygons * sizeof(s21_polygon));
  for (int i = 0; i < object->num_of_polygons; i++) {
    object->polygons[i].vertices = malloc(POLYGON_SIZE * sizeof(s21_vertex));
  }
  if (object->polygons == NULL) {
    printf("Memory error\n");
  } else {
    fseek(fp, 0, SEEK_SET);
    int polygon_index = 0, vertex_index = 0, vertex_count = 0;
    double x = 0, y = 0, z = 0;
    int v1 = 0, v2 = 0, v3 = 0, ch = 0;
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == 'v') {
        if (fscanf(fp, "%lf %lf %lf", &x, &y, &z) == 3) {
          vertex[vertex_index].x = x;
          vertex[vertex_index].y = y;
          vertex[vertex_index].z = z;
          vertex[vertex_index].vertex_number = vertex_count + 1;
          vertex_index++;
        }
        vertex_count++;
      } else if (ch == 'f') {
        if (fscanf(fp, "%d %d %d", &v1, &v2, &v3) == 3) {
          object->polygons[polygon_index].vertices[0] = vertex[v1 - 1];
          object->polygons[polygon_index].vertices[1] = vertex[v2 - 1];
          object->polygons[polygon_index].vertices[2] = vertex[v3 - 1];
          polygon_index++;
        }
      }
    }
  }
  free(vertex);
  for (int i = 0; i < object->num_of_polygons; i++) {
    free(object->polygons[i].vertices);
  }
  free(object->polygons);
  fclose(fp);
}
