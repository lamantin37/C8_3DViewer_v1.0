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
  char filename[512] = "models/empty.obj";
  fp = fopen(filename, "r");
  object.polygons = NULL;
  object.num_of_polygons = 0;
  object.num_of_vertices = 0;
  s21_vertex vertex;
  num_of_vert = parser_counter(fp, &object);
  object_parser(fp, &object, &vertex, num_of_vert);
  ck_assert_int_eq(object.num_of_vertices, 1);
  ck_assert_int_eq(object.num_of_polygons, 1);
}
END_TEST

START_TEST(test_parser5) {
  FILE* fp;
  int num_of_vert = 0;
  s21_object object;
  char filename[512] = "models/minicooper.obj";
  fp = fopen(filename, "r");
  object.polygons = NULL;
  object.num_of_polygons = 0;
  object.num_of_vertices = 0;
  s21_vertex vertex;
  num_of_vert = parser_counter(fp, &object);
  object_parser(fp, &object, &vertex, num_of_vert);
  ck_assert_int_eq(object.num_of_vertices, 44436);
  ck_assert_int_eq(object.num_of_polygons, 79759);
}
END_TEST

START_TEST(test_move1) {
  matrix_t cur_point = {0};
  matrix_t result = {0};
  s21_create_matrix(4, 1, &cur_point);
  cur_point.matrix[0][0] = 1;
  cur_point.matrix[1][0] = 2;
  cur_point.matrix[2][0] = 3;
  cur_point.matrix[3][0] = 4;
  move(0.6, -51, 75, &cur_point, &result);
  ck_assert_ldouble_eq_tol(result.matrix[0][0], 3.4, 1e-6);
  ck_assert_double_eq(result.matrix[1][0], -202);
  ck_assert_double_eq(result.matrix[2][0], 303);
  ck_assert_double_eq(result.matrix[3][0], 4);
  s21_remove_matrix(&cur_point);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_move2) {
  matrix_t cur_point = {0};
  matrix_t result = {0};
  s21_create_matrix(4, 1, &cur_point);
  cur_point.matrix[0][0] = -1.1;
  cur_point.matrix[1][0] = -2.2;
  cur_point.matrix[2][0] = -3.3;
  cur_point.matrix[3][0] = -4.4;
  move(0, 0, 0, &cur_point, &result);
  ck_assert_ldouble_eq_tol(result.matrix[0][0], -1.1, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], -2.2, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[2][0], -3.3, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[3][0], -4.4, 1e-6);
  s21_remove_matrix(&cur_point);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_rotate1) {
  matrix_t cur_point = {0};
  matrix_t result = {0};
  s21_create_matrix(4, 1, &cur_point);
  cur_point.matrix[0][0] = -1.1;
  cur_point.matrix[1][0] = -2.2;
  cur_point.matrix[2][0] = -3.3;
  cur_point.matrix[3][0] = -4.4;
  rotate(70, 0, 0, &cur_point, &result);
  ck_assert_ldouble_eq_tol(result.matrix[0][0], -1.1, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], 1.1605352, 1e-4);
  ck_assert_ldouble_eq_tol(result.matrix[2][0], -3.7925129, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[3][0], -4.4, 1e-6);
  s21_remove_matrix(&cur_point);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_rotate2) {
  matrix_t cur_point = {0};
  matrix_t result = {0};
  s21_create_matrix(4, 1, &cur_point);
  cur_point.matrix[0][0] = 1111;
  cur_point.matrix[1][0] = 222;
  cur_point.matrix[2][0] = 33;
  cur_point.matrix[3][0] = 4;
  rotate(0, 0.5, 0, &cur_point, &result);
  ck_assert_ldouble_eq_tol(result.matrix[0][0], 990.815, 1e-3);
  ck_assert_double_eq(result.matrix[1][0], 222);
  ck_assert_ldouble_eq_tol(result.matrix[2][0], -503.682, 1e-3);
  ck_assert_double_eq(result.matrix[3][0], 4);
  s21_remove_matrix(&cur_point);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_rotate3) {
  matrix_t cur_point = {0};
  matrix_t result = {0};
  s21_create_matrix(4, 1, &cur_point);
  cur_point.matrix[0][0] = 0;
  cur_point.matrix[1][0] = 777;
  cur_point.matrix[2][0] = 22;
  cur_point.matrix[3][0] = 0;
  rotate(0, 0, -110, &cur_point, &result);
  ck_assert_ldouble_eq_tol(result.matrix[0][0], -34.3766, 1e-4);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], -776.23854, 1e-3);
  ck_assert_ldouble_eq_tol(result.matrix[2][0], 22, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[3][0], 0, 1e-6);
  s21_remove_matrix(&cur_point);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_scale1) {
  matrix_t cur_point = {0};
  matrix_t result = {0};
  s21_create_matrix(4, 1, &cur_point);
  cur_point.matrix[0][0] = 345;
  cur_point.matrix[1][0] = -532;
  cur_point.matrix[2][0] = 0.05;
  cur_point.matrix[3][0] = 1;
  scale(-20, -40.4, -60.06, &cur_point, &result);
  ck_assert_ldouble_eq_tol(result.matrix[0][0], -6900, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], 21492.8, 1e-1);
  ck_assert_ldouble_eq_tol(result.matrix[2][0], -3.003, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[3][0], 1, 1e-6);
  s21_remove_matrix(&cur_point);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_scale2) {
  matrix_t cur_point = {0};
  matrix_t result = {0};
  s21_create_matrix(4, 1, &cur_point);
  cur_point.matrix[0][0] = 345;
  cur_point.matrix[1][0] = -532;
  cur_point.matrix[2][0] = 0.05;
  cur_point.matrix[3][0] = 1;
  scale(20, 40.4, 60.06, &cur_point, &result);
  ck_assert_ldouble_eq_tol(result.matrix[0][0], 6900, 1e-2);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], -21492.8, 1e-1);
  ck_assert_ldouble_eq_tol(result.matrix[2][0], 3.003, 1e-6);
  ck_assert_ldouble_eq_tol(result.matrix[3][0], 1, 1e-6);
  s21_remove_matrix(&cur_point);
  s21_remove_matrix(&result);
}
END_TEST

Suite* Create_suite() {
  Suite* suite = suite_create("3DViewer tests");
  TCase* tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, test_parser1);
  tcase_add_test(tcase_core, test_parser2);
  tcase_add_test(tcase_core, test_parser3);
  tcase_add_test(tcase_core, test_parser4);
  tcase_add_test(tcase_core, test_parser5);
  tcase_add_test(tcase_core, test_move1);
  tcase_add_test(tcase_core, test_move2);
  tcase_add_test(tcase_core, test_rotate1);
  tcase_add_test(tcase_core, test_rotate2);
  tcase_add_test(tcase_core, test_rotate3);
  tcase_add_test(tcase_core, test_scale1);
  tcase_add_test(tcase_core, test_scale2);
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