#include <check.h>
#include <math.h>
#include <stdio.h>

#include "auxiliary_modules.h"

int parser_counter(FILE*, s21_object*);
void object_parser(FILE*, s21_object*, s21_vertex*, int);

START_TEST(test_parser1) {
  FILE* fp;
  int num_of_vert = 0;
  s21_object object;
  char filename[512] = "models/teapot.obj";
  fp = fopen(filename, "r");
  object.polygons = NULL;
  object.num_of_polygons = 0;
  object.num_of_vertices = 0;
  s21_vertex vertex;
  num_of_vert = parser_counter(fp, &object);
  object_parser(fp, &object, &vertex, num_of_vert);
  ck_assert_int_eq(object.num_of_vertices, 3644);
  ck_assert_int_eq(object.num_of_polygons, 6320);
}
END_TEST

START_TEST(test_parser2) {
  FILE* fp;
  int num_of_vert = 0;
  s21_object object;
  char filename[512] = "models/capybara.obj";
  fp = fopen(filename, "r");
  object.polygons = NULL;
  object.num_of_polygons = 0;
  object.num_of_vertices = 0;
  s21_vertex vertex;
  num_of_vert = parser_counter(fp, &object);
  object_parser(fp, &object, &vertex, num_of_vert);
  ck_assert_int_eq(object.num_of_vertices, 7116);
  ck_assert_int_eq(object.num_of_polygons, 7114);
}
END_TEST

START_TEST(test_parser3) {
  FILE* fp;
  int num_of_vert = 0;
  s21_object object;
  char filename[512] = "models/apple.obj";
  fp = fopen(filename, "r");
  object.polygons = NULL;
  object.num_of_polygons = 0;
  object.num_of_vertices = 0;
  s21_vertex vertex;
  num_of_vert = parser_counter(fp, &object);
  object_parser(fp, &object, &vertex, num_of_vert);
  ck_assert_int_eq(object.num_of_vertices, 476);
  ck_assert_int_eq(object.num_of_polygons, 492);
}
END_TEST

START_TEST(test_parser4) {
  FILE* fp;
  int num_of_vert = 0;
  s21_object object;
  char filename[512] = "models/teapot.obj";
  fp = fopen(filename, "r");
  object.polygons = NULL;
  object.num_of_polygons = 0;
  object.num_of_vertices = 0;
  s21_vertex vertex;
  num_of_vert = parser_counter(fp, &object);
  object_parser(fp, &object, &vertex, num_of_vert);
  ck_assert_int_eq(object.num_of_vertices, 3644);
  ck_assert_int_eq(object.num_of_polygons, 6320);
}
END_TEST

Suite* Create_suite() {
  Suite* suite = suite_create("3DViewer tests");
  TCase* tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, test_parser1);
  tcase_add_test(tcase_core, test_parser2);
  tcase_add_test(tcase_core, test_parser3);
  // tcase_add_test(tcase_core, test_parser4);
  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite* suite = Create_suite();
  SRunner* suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  if (failed_count != 0) {
    printf("Failed tests: %d\n", failed_count);
    return EXIT_FAILURE;
  } else {
    printf("Success\n");
  }
  return EXIT_SUCCESS;
}
