import yt_libyt, yt, libyt

def test_function():
    ds = yt_libyt.libytDataset()
    ds.print_stats()

    # proj = yt.ProjectionPlot(ds, "x", ("gamer", "CCTwos"))
    # proj.annotate_grids()
    # proj.save('CCTwos.png')

    libyt.derived_func(1, "DerivedOnes")