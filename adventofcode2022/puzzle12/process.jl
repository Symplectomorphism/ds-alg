using PyPlot
using CSV
using DataFrames

file = CSV.File(open("trajectory.csv"); header=false);
df = DataFrame(file);

x = df[:,1]
y = df[:,2]

fig = figure(1, figsize=(25, 6))
fig.clf()
ax = PyPlot.subplot(1,1,1);
ax.plot(x, y, linewidth=3);
ax.set_xlim(-0.3,170);
ax.set_ylim(-40,0.3);
ax.set_xlabel(L"x", fontsize=15)
ax.set_ylabel(L"y", fontsize=15)
ax.tick_params(axis="both", labelsize=15)

fig.savefig("trajectory.svg", dpi=1200, format="svg", bbox_inches="tight")
fig.savefig("trajectory.png", dpi=600, format="png", bbox_inches="tight")
