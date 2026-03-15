# Library Checker gap report

更新日: 2026-03-15

## 集計方法

- 公式 `yosupo06/library-checker-problems` の `info.toml` がある問題ディレクトリを問題一覧として採用した。
- この repo の `test/*.test.cpp` にある `https://judge.yosupo.jp/problem/...` を既存 verify とみなした。
- `test/*` と `sample/*` の内部用ディレクトリは未対応数からは除外した。
- したがって、このレポートの「未対応」は「Library Checker 向け verify がまだ無い」を意味する。実装だけあって未 verify のものを含む。

## 件数

- 公式問題ディレクトリ: 259
- 既存 Yosupo verify: 87
- raw 差分: 172
- `test/*`, `sample/*` を除いた未対応候補: 162

## 未対応候補のカテゴリ別件数

- `data_structure`: 27
- `graph`: 21
- `polynomial`: 18
- `enumerative_combinatorics`: 16
- `linear_algebra`: 15
- `number_theory`: 14
- `tree`: 13
- `convolution`: 11
- `geo`: 7
- `string`: 6
- `big_integer`: 6
- `set_power_series`: 4
- `other`: 4

## 未対応候補一覧

### big_integer

- `addition_of_big_integers`
- `addition_of_hex_big_integers`
- `division_of_big_integers`
- `division_of_hex_big_integers`
- `multiplication_of_big_integers`
- `multiplication_of_hex_big_integers`

### convolution

- `bitwise_xor_convolution`
- `convolution_F_2_64`
- `convolution_mod_2_64`
- `convolution_mod_large`
- `gcd_convolution`
- `lcm_convolution`
- `min_plus_convolution_concave_arbitrary`
- `mul_mod2n_convolution`
- `mul_modp_convolution`
- `multivariate_convolution`
- `multivariate_convolution_cyclic`

### data_structure

- `associative_array`
- `deque`
- `double_ended_priority_queue`
- `dynamic_point_set_rectangle_affine_rectangle_sum`
- `majority_voting`
- `ordered_set`
- `persistent_queue`
- `persistent_range_affine_range_sum`
- `point_set_range_composite_large_array`
- `point_set_range_frequency`
- `point_set_range_sort_range_composite`
- `predecessor_problem`
- `range_add_range_min`
- `range_affine_range_sum_large_array`
- `range_kth_smallest`
- `range_linear_add_range_min`
- `range_parallel_unionfind`
- `range_reverse_range_sum`
- `range_set_range_composite`
- `static_range_count_distinct`
- `static_range_lis_query`
- `static_range_mode_query`
- `static_range_sum`
- `static_range_sum_with_upper_bound`
- `static_rectangle_add_rectangle_sum`
- `unionfind_with_potential`
- `unionfind_with_potential_non_commutative_group`

### enumerative_combinatorics

- `bell_number`
- `binomial_coefficient_prime_mod`
- `factorial`
- `many_factorials`
- `montmort_number_mod`
- `number_of_increasing_sequences_between_two_sequences`
- `number_of_subsequences`
- `partition_function`
- `q_binomial_coefficient_prime_mod`
- `sharp_p_subset_sum`
- `stirling_number_of_the_first_kind`
- `stirling_number_of_the_first_kind_fixed_k`
- `stirling_number_of_the_first_kind_small_p_large_n`
- `stirling_number_of_the_second_kind`
- `stirling_number_of_the_second_kind_fixed_k`
- `stirling_number_of_the_second_kind_small_p_large_n`

### geo

- `convex_layers`
- `count_points_in_triangle`
- `euclidean_mst`
- `furthest_pair`
- `manhattanmst`
- `minimum_enclosing_circle`
- `sort_points_by_argument`

### graph

- `bipartite_edge_coloring`
- `chordal_graph_recognition`
- `chromatic_number`
- `chromatic_polynomial`
- `connected_components_of_complement_graph`
- `counting_c4`
- `counting_eulerian_circuits`
- `counting_spanning_tree_directed`
- `counting_spanning_tree_undirected`
- `enumerate_cliques`
- `enumerate_triangles`
- `general_weighted_matching`
- `global_minimum_cut_of_dynamic_star_augmented_graph`
- `incremental_minimum_spanning_forest`
- `incremental_scc`
- `k_shortest_walk`
- `minimum_diameter_spanning_tree`
- `minimum_steiner_tree`
- `st_numbering`
- `three_edge_connected_components`
- `tree_decomposition_width_2`

### linear_algebra

- `adjugate_matrix`
- `characteristic_polynomial`
- `hafnian_of_matrix`
- `intersection_of_f2_vector_spaces`
- `inverse_matrix_mod_2`
- `matrix_det_arbitrary_mod`
- `matrix_det_mod_2`
- `matrix_product`
- `matrix_product_mod_2`
- `matrix_rank`
- `matrix_rank_mod_2`
- `pfaffian_of_matrix`
- `pow_of_matrix`
- `sparse_matrix_det`
- `system_of_linear_equations_mod_2`

### number_theory

- `bernoulli_number`
- `counting_squarefrees`
- `dirichlet_convolution_and_prefix_sums`
- `dirichlet_inverse_and_prefix_sums`
- `discrete_logarithm_fixed_mod`
- `enumerate_quotients`
- `gcd_of_gaussian_integers`
- `kth_root_mod`
- `min_of_mod_of_linear`
- `nim_product_64`
- `rational_approximation`
- `sum_of_multiplicative_function`
- `sum_of_multiplicative_function_large`
- `two_square_sum`

### other

- `consecutive_terms_of_linear_recurrent_sequence`
- `longest_increasing_subsequence`
- `sum_of_exponential_times_polynomial`
- `sum_of_exponential_times_polynomial_limit`

### polynomial

- `composition_of_formal_power_series`
- `composition_of_formal_power_series_large`
- `compositional_inverse_of_formal_power_series`
- `compositional_inverse_of_formal_power_series_large`
- `conversion_from_monomial_basis_to_newton_basis`
- `division_of_polynomials`
- `exp_of_formal_power_series_sparse`
- `inv_of_formal_power_series`
- `inv_of_formal_power_series_2d`
- `inv_of_formal_power_series_sparse`
- `inv_of_polynomials`
- `log_of_formal_power_series_sparse`
- `multipoint_evaluation_on_geometric_sequence`
- `polynomial_interpolation_on_geometric_sequence`
- `polynomial_root_finding`
- `pow_of_formal_power_series_sparse`
- `product_of_polynomial_sequence`
- `sqrt_of_formal_power_series_sparse`

### set_power_series

- `exp_of_set_power_series`
- `log_of_set_power_series`
- `polynomial_composite_set_power_series`
- `power_projection_of_set_power_series`

### string

- `aho_corasick`
- `longest_common_substring`
- `palindromes_in_deque`
- `prefix_substring_lcs`
- `runenumerate`
- `wildcard_pattern_matching`

### tree

- `common_interval_decomposition_tree`
- `dynamic_tree_subtree_add_subtree_sum`
- `dynamic_tree_vertex_add_path_sum`
- `dynamic_tree_vertex_add_subtree_sum`
- `point_set_tree_path_composite_sum`
- `point_set_tree_path_composite_sum_fixed_root`
- `rooted_tree_topological_order_with_minimum_inversions`
- `tree_diameter`
- `tree_path_composite_sum`
- `vertex_add_path_sum`
- `vertex_add_range_contour_sum_on_tree`
- `vertex_get_range_contour_add_on_tree`

## 除外した内部用ディレクトリ

- `sample/many_aplusb_128bit`
- `test/allow_re`
- `test/allow_tle`
- `test/differ_id`
- `test/failed_verify`
- `test/no_title`
- `test/other_checker_place`
- `test/other_verifier_place`
- `test/simple_aplusb`
- `test/unused_gen`
