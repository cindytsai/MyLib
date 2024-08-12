import yt_libyt, yt, libyt
import numpy as np

yt.set_log_level(10)

def test_function():
    ds = yt_libyt.libytDataset()
    ds.print_stats()
    print("---------------------")
    field = 'Dens'

    # TODO: derived function didn't read 'DerivedOnes'
    # zoom = 2
    # box  = ds.box( ds.domain_center-0.5/zoom*ds.domain_width,
    #                ds.domain_center+0.5/zoom*ds.domain_width )
    # pz_dens = yt.ProjectionPlot( ds, 'z', ('gamer', field),
    #                              weight_field=('index','ones'),
    #                              center='c',
    #                              data_source=box,
    #                              width=ds.domain_width[0]/zoom )
    # pz_dens.set_axes_unit( 'kpc' )
    # pz_dens.set_unit( ('gamer', field), "Msun/kpc**3" )
    # pz_dens.set_zlim( ('gamer', field), 3.0e1, 3.0e5   )
    # pz_dens.set_cmap( ('gamer', field), 'viridis' )
    # pz_dens.set_background_color( ('gamer', field) )
    # pz_dens.annotate_timestamp( time_unit='Myr', corner='upper_right' )
    # pz_dens.annotate_grids()
    # pz_dens.save()

    slc = yt.SlicePlot(ds, 'z', ('gamer', field), center='c')
    slc.save()

    print("---------------------")
    array_derived_func = libyt.derived_func(1, field)
    print(array_derived_func.shape)
    print(len(np.unique(array_derived_func)))
    print(type(array_derived_func))
    for k in range(array_derived_func.shape[0]):
        for j in range(array_derived_func.shape[1]):
            for i in range(array_derived_func.shape[2]):
                print(i, j, k, array_derived_func[k, j, i])



