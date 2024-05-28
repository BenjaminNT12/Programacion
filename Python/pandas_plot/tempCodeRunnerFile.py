# parameters
background_color = '#0d1b2a'
text_color = '#fefae0'
line_color = '#d90429'
dpi = 50

# Setting up the plot
fig, ax = plt.subplots(figsize=(10, 6), dpi=dpi)
fig.set_facecolor(background_color)
ax.set_facecolor(background_color)
ax.tick_params(axis='y', colors=text_color)
ax.spines[['left']].set_color(text_color)