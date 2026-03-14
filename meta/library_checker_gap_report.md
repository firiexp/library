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

## 優先度付き shortlist

### Priority A

既存実装が直接あり、既存 verify の流用や軽いラッパで追加しやすいもの。

| problem | 根拠 | 主なファイル |
| --- | --- | --- |
| `bitwise_xor_convolution` | 専用実装あり。AOJ verify あり。 | `math/fwht.cpp`, `test/aoj0402.test.cpp` |
| `unionfind_with_potential` | 専用実装あり。AOJ verify あり。 | `datastructure/weightedunionfind.cpp`, `test/aoj_dsl_1_b_weightedunionfind.test.cpp` |
| `manhattanmst` | 専用実装あり。AOJ verify あり。 | `graph/manhattanmst.cpp`, `test/aoj0403.test.cpp` |
| `many_factorials` | 専用実装あり。別 verify で利用実績あり。 | `math/factorial.cpp`, `test/aoj0452.test.cpp` |
| `discrete_logarithm_fixed_mod` | 専用実装あり。近縁の Yosupo verify が既にある。 | `math/discrete_logarithm.cpp`, `test/yosupo_discrete_logarithm_mod.test.cpp` |
| `tree_diameter` | 専用実装あり。重み付き版 verify あり。 | `tree/diameter.cpp`, `tree/diameter_weighted.cpp`, `test/aoj_grl_5_a_diameter.test.cpp` |
| `matrix_rank` | 主要処理は既に verify 済みの消去法。 | `math/gauss_jordan_mint.cpp`, `test/yosupo_system_of_linear_equations.test.cpp` |
| `matrix_product` | 直接使える行列積実装あり。wrapper が薄い。 | `math/matrix.cpp` |
| `point_set_tree_path_composite_sum` | HLD + segtree の既存 verify をかなり流用できる。 | `tree/hld.cpp`, `datastructure/segtree.cpp`, `test/yosupo_vertex_set_path_composite_hld_helper.test.cpp` |
| `point_set_tree_path_composite_sum_fixed_root` | 上と同じく HLD 系の流用が効く。 | `tree/hld.cpp`, `datastructure/segtree.cpp` |
| `aho_corasick` | 専用実装と docs がある。 | `datastructure/ahocorasick.cpp`, `_md/ahocorasick.md` |

### Priority B

専用実装か強い部品があり、verify 追加は十分現実的だが A より少し設計が要るもの。

| problem | 根拠 | 主なファイル |
| --- | --- | --- |
| `gcd_convolution` | 専用変換実装あり。 | `math/gcd_transform.cpp`, `_md/gcd_transform.md` |
| `vertex_add_path_sum` | HLD の既存部品で書ける。 | `tree/hld.cpp`, `datastructure/segtree.cpp`, `datastructure/binaryindexedtree.cpp` |
| `tree_path_composite_sum` | ordered path query を HLD が持つ。 | `tree/hld.cpp`, `test/yosupo_vertex_set_path_composite_hld_helper.test.cpp` |
| `dynamic_tree_vertex_add_path_sum` | Link-Cut Tree の fold がそのまま近い。 | `tree/link_cut_tree.cpp`, `test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp` |
| `range_reverse_range_sum` | Implicit Treap が reverse / fold を持つ。 | `datastructure/implicit_treap.cpp` |
| `deque` | Implicit Treap で操作を吸える。 | `datastructure/implicit_treap.cpp`, `datastructure/swag_deque.cpp` |
| `longest_common_substring` | suffix automaton / suffix array / LCP 系部品はある。 | `string/suffix_automaton.cpp`, `string/suffix_array.cpp`, `string/lcs_bit.cpp` |

### Priority C

一部の部品はあるが、Library Checker 問題に対してそのまま足りるか再確認が必要なもの。

| problem | 懸念 | 主なファイル |
| --- | --- | --- |
| `dynamic_tree_vertex_add_subtree_sum` | 現在の Link-Cut Tree だけでは subtree 集約がそのまま出ない。 | `tree/link_cut_tree.cpp` |
| `point_set_range_frequency` | 現在の Wavelet Matrix は静的。point-set 更新には不足。 | `datastructure/wavelet_matrix.cpp` |
| `static_range_count_distinct` | Mo や Wavelet Matrix はあるが専用解が未整理。 | `util/mo.cpp`, `datastructure/wavelet_matrix.cpp` |
| `wildcard_pattern_matching` | 文字列部品はあるが専用実装は見えない。 | `string/rolling_hash.cpp`, `string/kmp.cpp` |

## 次に着手するならこの順

1. `unionfind_with_potential`
2. `bitwise_xor_convolution`
3. `manhattanmst`
4. `many_factorials`
5. `discrete_logarithm_fixed_mod`
6. `tree_diameter`
7. `matrix_rank`
8. `matrix_product`
9. `point_set_tree_path_composite_sum`
10. `aho_corasick`

理由:

- 既存実装が薄く明確で、verify のみ追加する形に近い。
- 既に AOJ/Yosupo の近縁 verify があり、実装リスクより wrapper リスクが主になる。
- 1 問ごとの工数が比較的小さく、短時間で coverage を増やせる。

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
