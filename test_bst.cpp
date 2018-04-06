	/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			test_bst.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include "general.h"
#include "shortcut.h"
#include "bst.h"
#include "test_bst.h"


#define ELEMENTS_COUNT 14
static int elements_to_add[ELEMENTS_COUNT] = {
	11, 5, 28, 2, 7, 17, 29, 1, 3, 13, 27, 42, 53, 20
};

TEST(create_bst)
{
	init_free_list();

	Bst  bst = new_bst();
	ASSERT_TRUE(bst == 0, "new bst expected to be 0");
	ASSERT_EQUALS(0, get_depth(bst));
	delete_bst(bst);
	ASSERT_EQUALS(0, get_free_list_length());
}

TEST(add_one)
{
	init_free_list();

	Bst bst = new_bst();

	add(&bst, 11);
	ASSERT_EQUALS(1, get_depth(bst));
	ASSERT_EQUALS(11, root_value(bst));
	ASSERT_TRUE(left_subtree(bst) == 0, "Left subtree expected to be 0");
	ASSERT_TRUE(right_subtree(bst) == 0, "Right subtree expected to be 0");

	delete_bst(bst);
	ASSERT_TRUE(bst == get_free_list()[0], "bst expected to be deleted tree");
}

TEST(add_more)
{
	init_free_list();

	Bst bst = new_bst();

	add(&bst, 11);
	add(&bst, 5);
	add(&bst, 28);
	ASSERT_EQUALS(2, get_depth(bst));
	ASSERT_EQUALS(5, root_value(left_subtree(bst)));
	ASSERT_EQUALS(28, root_value(right_subtree(bst)));
	delete_bst(bst);
	ASSERT_EQUALS(3, get_free_list_length());
}

static void add_all_elements(Bst* bst);
TEST(add_many)
{
	init_free_list();

	Bst bst = new_bst();
	add_all_elements(&bst);

	ASSERT_EQUALS(5, get_depth(bst));
	ASSERT_EQUALS(3, get_depth(left_subtree(bst)));
	ASSERT_EQUALS(4, get_depth(right_subtree(bst)));

	ASSERT_EQUALS(11, root_value(bst));
	ASSERT_EQUALS(5, root_value(left_subtree(bst)));
	ASSERT_EQUALS(28, root_value(right_subtree(bst)));

	delete_bst(bst);
	ASSERT_EQUALS(ELEMENTS_COUNT, get_free_list_length());
}

static void add_all_elements(Bst* bst)
{
	for (int i = 0; i < ELEMENTS_COUNT; i++)
		add(bst, elements_to_add[i]);
}

TEST(traversal_pre_order)
{
	Bst bst = new_bst();
	add_all_elements(&bst);

	int pre_order_elements[ELEMENTS_COUNT] = {
		11, 5, 2, 1, 3, 7, 28, 17, 13, 27, 20, 29, 42, 53
	};
	int elements[ELEMENTS_COUNT];

	int elements_count = traverse_pre_order(bst, elements, 0);
	ASSERT_EQUALS(ELEMENTS_COUNT, elements_count);
	for (int i = 0; i < elements_count; i++)
		ASSERT_EQUALS(pre_order_elements[i], elements[i]);

}

TEST(traversal_in_order)
{
	Bst bst = new_bst();
	add_all_elements(&bst);

	int in_order_elements[ELEMENTS_COUNT] = {
		1, 2, 3, 5, 7, 11, 13, 17, 20, 27, 28, 29, 42, 53
	};
	int elements[ELEMENTS_COUNT];

	int elements_count = traverse_in_order(bst, elements, 0);
	ASSERT_EQUALS(ELEMENTS_COUNT, elements_count);
	for (int i = 0; i < elements_count; i++)
		ASSERT_EQUALS(in_order_elements[i], elements[i]);


}

TEST(traversal_post_order)
{
	Bst bst = new_bst();
	add_all_elements(&bst);

	int post_order_elements[ELEMENTS_COUNT] = {
		1, 3, 2, 7, 5, 13, 20, 27, 17, 53, 42, 29, 28, 11
	};
	int elements[ELEMENTS_COUNT];

	int elements_count = traverse_post_order(bst, elements, 0);
	for (int i = 0; i < elements_count; i++)
		ASSERT_EQUALS(post_order_elements[i], elements[i]);


}

TEST(equality_of_empty_trees)
{
	Bst bst1 = new_bst();
	Bst bst2 = new_bst();
	ASSERT_TRUE(are_equal(bst1, bst2), "expected to be equal");
}

TEST(equality_of_roots)
{
	Bst bst1 = new_bst();
	Bst bst2 = new_bst();
	add(&bst1, 5);
	add(&bst2, 5);
	ASSERT_TRUE(are_equal(bst1, bst2), "expected to be equal");
}

TEST(unequal_roots)
{
	Bst bst1 = new_bst();
	Bst bst2 = new_bst();
	add(&bst1, 5);
	add(&bst2, 6);
	ASSERT_FALSE(are_equal(bst1, bst2), "expected to be unequal");
}

TEST(equality)
{
	Bst bst1 = new_bst();
	Bst bst2 = new_bst();
	add_all_elements(&bst1);
	add_all_elements(&bst2);
	ASSERT_TRUE(are_equal(bst1, bst2), "expected to be equal");
}

TEST(unequal_depths)
{
	Bst bst1 = new_bst();
	Bst bst2 = new_bst();
	add_all_elements(&bst1);
	add_all_elements(&bst2);
	add(&bst1, 100);
	ASSERT_FALSE(are_equal(bst1, bst2), "expected to be unequal");
}

TEST(same_layout_different_nodes)
{
	Bst bst1 = new_bst();
	Bst bst2 = new_bst();
	add(&bst1, 11);
	add(&bst2, 11);
	add(&bst1, 5);
	add(&bst2, 5);
	add(&bst1, 28);
	add(&bst2, 28);
	add(&bst1, 17);
	add(&bst2, 15);
	ASSERT_FALSE(are_equal(bst1, bst2), "expected to be unequal");
}

TEST(number_of_subtrees_of_empty_tree)
{
	Bst bst = new_bst();
	ASSERT_EQUALS(-1, get_number_of_subtrees(bst));
}

TEST(number_of_subtrees_of_single_node)
{
	Bst bst = new_bst();
	add(&bst, 5);
	ASSERT_EQUALS(0, get_number_of_subtrees(bst));
}

TEST(number_of_subtrees_of_two_nodes)  //the step
{
	Bst bst = new_bst();
	add(&bst, 5);
	add(&bst, 3);
	ASSERT_EQUALS(1, get_number_of_subtrees(bst));
}

TEST(number_of_subtrees_of_three_nodes) // assurance test
{
	Bst bst = new_bst();
	add(&bst, 5);
	add(&bst, 3);
	add(&bst, 1);
	ASSERT_EQUALS(2, get_number_of_subtrees(bst));
}

TEST(number_of_subtrees_of_small_tree) // the second step
{
	Bst bst = new_bst();
	add(&bst, 5);
	add(&bst, 3);
	add(&bst, 7);
	ASSERT_EQUALS(2, get_number_of_subtrees(bst));
}

TEST(number_of_subtrees)
{
	Bst bst = new_bst();
	add_all_elements(&bst);
	ASSERT_EQUALS(13, get_number_of_subtrees(bst));
}

TEST(most_left_longest_branch_of_empty_tree)
{
	Bst bst = new_bst();
	Bst expected_longest = new_bst();
	Bst longest = new_bst();
	most_left_longest_branch(bst, &longest);
	ASSERT_TRUE(are_equal(expected_longest, longest), "expected to be equal");
	ASSERT_TRUE(longest == 0, "NEW!! expected to be 0");
}

TEST(most_left_longest_branch)
{
	Bst bst = new_bst();
	add_all_elements(&bst);

	Bst expected_longest = new_bst();
	add(&expected_longest, 11);
	add(&expected_longest, 28);
	add(&expected_longest, 17);
	add(&expected_longest, 27);
	add(&expected_longest, 20);

	Bst longest = new_bst();
	most_left_longest_branch(bst, &longest);

	ASSERT_TRUE(are_equal(expected_longest, longest), "OLD!! expected to be equal");
	ASSERT_EQUALS(11, root_value(longest));
	ASSERT_EQUALS(28, root_value(right_subtree(longest)));
	ASSERT_EQUALS(17, root_value(left_subtree(right_subtree(longest))));
	ASSERT_EQUALS(27, root_value(right_subtree(left_subtree(right_subtree(longest)))));
	ASSERT_EQUALS(20, root_value(left_subtree(right_subtree(left_subtree(right_subtree(longest))))));
}
