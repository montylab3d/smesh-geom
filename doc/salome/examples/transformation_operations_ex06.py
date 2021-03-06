# Offset Surface

import salome
salome.salome_init_without_session()
import GEOM
from salome.geom import geomBuilder
geompy = geomBuilder.New()
gg = salome.ImportComponentGUI("GEOM")

# create a box and a sphere
box = geompy.MakeBox(20, 20, 20, 200, 200, 200)

# create a new object as offset of the given object
offset  = geompy.MakeOffset(box, 70.)
offset2 = geompy.MakeOffsetIntersectionJoin(box, 70.)

# add objects in the study
id_box = geompy.addToStudy(box, "Box")
id_offset = geompy.addToStudy(offset, "Offset")
id_offset2 = geompy.addToStudy(offset2, "Offset_intersection_join")

# display the results
gg.createAndDisplayGO(id_box)
gg.setDisplayMode(id_box,1)
gg.createAndDisplayGO(id_offset)
gg.createAndDisplayGO(id_offset2)
