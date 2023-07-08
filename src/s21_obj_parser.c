#include "s21_object.h"

void parser_counter(FILE* fp, s21_polygon* polygon, s21_object* object) {
  char line[256];
  while (fgets(line, sizeof(line), fp)) {
    if (line[0] != '\n' && line[0] != '#') {
      char token[3];
      if (sscanf(line, "%2s", token) == 1) {
        if (strcmp(token, "f") == 0) {
          object->num_of_polygons += 1;
        } else if (strcmp(token, "v") == 0) {
          polygon->num_of_vertices += 1;
        }
      }
    }
  }
}

void object_parser(FILE* fp, s21_object * object, s21_polygon* polygon) {
  object->polygons = malloc(object->num_of_polygons * sizeof(s21_polygon));
  for (int i = 0; i < object->num_of_polygons; i++) {
    object->polygons[i].vertices = malloc(3 * sizeof(s21_vertex));
  }
  if (object->polygons == NULL) {
    printf("Memory error\n");
  } else {
    fseek(fp, 0, SEEK_SET);
    int polygon_index = 0;
    int polygon_count = 0;
    int vertex_index = 0;
    double x, y, z;
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == 'v') {
        if (fscanf(fp, "%lf %lf %lf", &x, &y, &z) == 3) {
          if (vertex_index < polygon->num_of_vertices) {
            object->polygons[polygon_index].vertices[vertex_index].x = x;
            object->polygons[polygon_index].vertices[vertex_index].y = y;
            object->polygons[polygon_index].vertices[vertex_index].z = z;
            vertex_index++;
          }
        }
      } else if (ch == 'f') {
        object->polygons[polygon_index] = *polygon;
        polygon_index++;
        vertex_index = 0;
        if (polygon_index >= object->num_of_polygons) {
          break;
        }
      }
    }
  }
  fclose(fp);
}

void printPolygon(s21_object* object) {
  for (int j = 0; j < object->num_of_polygons; j++) {
    printf("Polygon %d with %d vertices:\n", j+1, object->polygons[j].num_of_vertices);
    for (int i = 0; i < object->polygons[j].num_of_vertices; i++) {
      printf("Vertex %d: (%lf, %lf, %lf)\n", i + 1, object->polygons[j].vertices[i].x, object->polygons[j].vertices[i].y, object->polygons[j].vertices[i].z);
    }
  }
  printf("\n");
}

int main() {
  FILE *fp;
  if ((fp = fopen("cube.obj", "r")) == NULL) {
    printf("Error opening file\n");
  } else {
    s21_object object;
    object.polygons = NULL;
    object.num_of_polygons = 0;

    s21_polygon polygon;
    polygon.vertices = NULL;
    polygon.num_of_vertices = 0;

    parser_counter(fp, &polygon, &object);
    printf("v = %d\nf = %d\n", polygon.num_of_vertices, object.num_of_polygons);
    object_parser(fp, &object, &polygon);
    printPolygon(&object);
  }
  return 0;
}