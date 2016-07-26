#CSPXLgen

====
Usage:
====
    CSPXLgen <outfile> --rand <nbVars> <domSize> <p1> <p2>
    where:
        outfile is the output file name
        nb-vars is the number of variables of the CSP. Variables are indexed in {0, ..., nbVars - 1}
        dom-size is the size of the variable's domain --- assumed to be all equal and in {0, ..., domSize - 1}
        p1 in [0, 1] is the density of constraint graph --- defined as p1 * ((nbVars * (nbVars - 1))/2)
        p2 in [0, 1] is the constraint tighness, which defines the number of elements in the relation
                     which are satisfied, as: p2 * (domSize^2).
====
Example:
====
    ./CSPXLgen test --rand 100000 5 0.3 0.5


The program generates 3 output files:
    outfile.cgxl : which contain the constraint graph formatted as follows:
        <var_1_idx> <var_11_idx> <var_12_idx> ... <varI_1n_1_idx>
        <var_2_idx> <var_21_idx> <var_22_idx> ... <varI_2n_2_idx>
        ...
        <var_N_idx> <var_N1_idx> <var_N2_idx> ... <varI_Nn_N_idx>

        where the each <var_i_idx> and <var_ij_idx> are variable indexes in {0, ..., nb-vars - 1}, and each line
        describe the neighboring relations between the first variable <var_i_idx> and its neighbors <var_ij_idx>

        Note: For efficiency reasons we output the neighboring constraints between variables var_i and var_j iff i < j

    outfile.dmxl contains the list of domains for the problem variables formatted as follows:
        <var_i_idx> 0 1 2 ... domSize - 1

        for all i in {0, ..., nbVars - 1}

    outfile.cnxl contains the list of constraints in formatted as follows:
        For a binary constraint between two variables var_i, var_j, with index i and j, respectively:
          <var_i_idx> <var_j_idx> i_val_1 j_val_1 i_val_2 j_val_2 ... i_val_n j_val_n

          where the i_val_k and j_val_k (for k = 1 .. n) are the pair of values for the variables var_i and var_j,
          repsectively, which are in the relation (i.e., they are satisfiable).

