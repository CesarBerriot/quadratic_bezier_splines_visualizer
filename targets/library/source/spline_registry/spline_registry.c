#include "spline_registry.h"
#include <malloc.h>

struct spline_registry_node * spline_registry;

static void cleanup_node(struct spline_registry_node *);

void register_spline(struct cbs_point spline[], int length, struct cbsv_color color)
{	struct spline_registry_node * node;

	if(spline_registry)
	{	struct spline_registry_node * iterator;
		for(iterator = spline_registry; iterator->next_node; iterator = iterator->next_node);
		iterator->next_node = malloc(sizeof(struct spline_registry_node));
		node = iterator->next_node;
	}
	else
	{	spline_registry = malloc(sizeof(struct spline_registry_node));
		node = spline_registry;
	}

	*node = (struct spline_registry_node)
	{	.points =
         {  .array = spline,
		    .length = length,
         },
		.color = color,
        .handle = cbs_load_spline(spline, length)
	};
}

void cleanup_spline_registry(void)
{	if(spline_registry)
	{	cleanup_node(spline_registry);
		spline_registry = NULL;
	}
}

static void cleanup_node(struct spline_registry_node * node)
{	if(node->next_node)
	{	cleanup_node(node->next_node);
        cbs_cleanup_spline(node->handle);
		free(node);
	}
}
