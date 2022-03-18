# trace generated using paraview version 5.10.0
#import paraview
#paraview.compatibility.major = 5
#paraview.compatibility.minor = 10

#### import the simple module from the paraview
import sys
from paraview.simple import *
#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

# get active source.
phi3000csv = CSVReader(FileName=[sys.argv[1]])

# create new layout object 'Layout #2'
layout1 = CreateLayout(name='Layout #1')

# find view
renderView1 = FindViewOrCreate('RenderView1', viewtype='RenderView')

# update the view to ensure updated data information
renderView1.Update()

# create a new 'Table To Structured Grid'
tableToStructuredGrid1 = TableToStructuredGrid(registrationName='TableToStructuredGrid1', Input=phi3000csv)
tableToStructuredGrid1.XColumn = ' P'
tableToStructuredGrid1.YColumn = ' P'
tableToStructuredGrid1.ZColumn = ' P'

# Properties modified on tableToStructuredGrid1
tableToStructuredGrid1.WholeExtent = [0, 99, 0, 99, 0, 99]
tableToStructuredGrid1.XColumn = ' x'
tableToStructuredGrid1.YColumn = 'y'
tableToStructuredGrid1.ZColumn = ' z'

# create a new 'Contour'
contour1 = Contour(registrationName='Contour1', Input=tableToStructuredGrid1)
contour1.ContourBy = ['POINTS', ' P']
contour1.Isosurfaces = [1.499536325]
contour1.PointMergeMethod = 'Uniform Binning'

# set active view
SetActiveView(renderView1)

# set active source
SetActiveSource(tableToStructuredGrid1)

# Properties modified on renderView1.AxesGrid
renderView1.AxesGrid.Visibility = 1

# get the material library
materialLibrary1 = GetMaterialLibrary()

# Properties modified on renderView1.AxesGrid
renderView1.AxesGrid.XTitleColor = [0.0, 0.0, 0.0]
renderView1.AxesGrid.YTitleColor = [0.0, 0.0, 0.0]
renderView1.AxesGrid.ZTitleColor = [0.0, 0.0, 0.0]
renderView1.AxesGrid.GridColor = [0.023529411764705882, 0.023529411764705882, 0.023529411764705882]
renderView1.AxesGrid.XLabelColor = [0.0, 0.0, 0.0]
renderView1.AxesGrid.YLabelColor = [0.0, 0.0, 0.0]
renderView1.AxesGrid.ZLabelColor = [0.0, 0.0, 0.0]

# set active source
SetActiveSource(contour1)

# set active source
SetActiveSource(contour1)

# show data in view
contour1Display = Show(contour1, renderView1, 'GeometryRepresentation')

# get color transfer function/color map for 'P'
pLUT = GetColorTransferFunction('P')

# trace defaults for the display properties.
contour1Display.Representation = 'Surface'
contour1Display.ColorArrayName = ['POINTS', ' P']
contour1Display.LookupTable = pLUT
contour1Display.SelectTCoordArray = 'None'
contour1Display.SelectNormalArray = 'Normals'
contour1Display.SelectTangentArray = 'None'
contour1Display.OSPRayScaleArray = ' P'
contour1Display.OSPRayScaleFunction = 'PiecewiseFunction'
contour1Display.SelectOrientationVectors = 'None'
contour1Display.ScaleFactor = 9.9
contour1Display.SelectScaleArray = ' P'
contour1Display.GlyphType = 'Arrow'
contour1Display.GlyphTableIndexArray = ' P'
contour1Display.GaussianRadius = 0.495
contour1Display.SetScaleArray = ['POINTS', ' P']
contour1Display.ScaleTransferFunction = 'PiecewiseFunction'
contour1Display.OpacityArray = ['POINTS', ' P']
contour1Display.OpacityTransferFunction = 'PiecewiseFunction'
contour1Display.DataAxesGrid = 'GridAxesRepresentation'
contour1Display.PolarAxes = 'PolarAxesRepresentation'

# init the 'PiecewiseFunction' selected for 'ScaleTransferFunction'
contour1Display.ScaleTransferFunction.Points = [1.4995362758636475, 0.0, 0.5, 0.0, 1.4997804164886475, 1.0, 0.5, 0.0]

# init the 'PiecewiseFunction' selected for 'OpacityTransferFunction'
contour1Display.OpacityTransferFunction.Points = [1.4995362758636475, 0.0, 0.5, 0.0, 1.4997804164886475, 1.0, 0.5, 0.0]

# show color bar/color legend
contour1Display.SetScalarBarVisibility(renderView1, True)

# reset view to fit data
renderView1.ResetCamera(False)

# get opacity transfer function/opacity map for 'P'
pPWF = GetOpacityTransferFunction('P')

# hide data in view
Hide(contour1, renderView1)

# show data in view
contour1Display = Show(contour1, renderView1, 'GeometryRepresentation')

# show color bar/color legend
contour1Display.SetScalarBarVisibility(renderView1, True)

# reset view to fit data
renderView1.ResetCamera(False)

# turn off scalar coloring
ColorBy(contour1Display, None)

# Hide the scalar bar for this color map if no visible data is colored by it.
HideScalarBarIfNotNeeded(pLUT, renderView1)

# change solid color
contour1Display.AmbientColor = [1.0, 0.16470588235294117, 0.16470588235294117]
contour1Display.DiffuseColor = [1.0, 0.16470588235294117, 0.16470588235294117]

# set active view
SetActiveView(renderView1)

# layout/tab size in pixels
layout1.SetSize(1556, 793)

# Properties modified on renderView1
renderView1.Background = [1.0, 1.0, 1.0]
renderView1.Update()

# current camera placement for renderView1
renderView1.CameraPosition = [50.0, 50.0, 400.0]
renderView1.CameraFocalPoint = [49.5, 49.5, 49.5]
renderView1.CameraParallelScale = 87.95479479289124

# save screenshot
SaveScreenshot(sys.argv[2], renderView1, StereoMode="No change", ImageResolution=[800, 800])
