#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "config.h"
#include "ast.h"
#include "parser.h"

int
parse_args (config_t *config, int argc, char *argv[])
{
    opterr = 0;     // Silence getopt error printing
    int opt;
    while ((opt = getopt(argc, argv, "n:pa")) != -1) {
        switch (opt) {
        case 'p':
            config->mode = MODE_PARSER;
            break;
        case 'a':
            config->mode = MODE_AST;
            break;
        case 'n':
        {
            char *end;
            config->iteration_number = strtoul (optarg, &end, 10);
            if (*end != '\0') {
                fprintf (stderr, "ERROR: n is not an integer\n");
                return (EXIT_FAILURE);
            }
            break;
        }
        case '?':
        default:
            fprintf (stderr, "ERROR: Unexpected flag\n");
            return (EXIT_FAILURE);
        }
    }

    config->expr = argv[optind];
    if (!config->expr) {
        fprintf (stderr, "ERROR: no expression was provided\n");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

int
main (int argc, char *argv[])
{
    config_t config = {
        .iteration_number = 1,
        .mode = MODE_PARSER,
    };
    if (parse_args (&config, argc, argv) != 0) {
        return (EXIT_FAILURE);
    }

    int returned;
    switch (config.mode) {
    case MODE_PARSER:
        returned = run_parser (&config);
        break;
    case MODE_AST:
        returned = run_ast (&config);
        break;
    default:
        fprintf (stderr, "ERROR: Unexpected calculator mode\n");
        return (EXIT_FAILURE);
    }

    if (returned != 0) {
        return (EXIT_FAILURE);
    }

    printf ("%Lg\n", config.result);

    return (EXIT_SUCCESS);
}