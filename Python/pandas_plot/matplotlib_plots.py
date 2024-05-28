# data manipulation
import pandas as pd
import numpy as np

# make the charts
import matplotlib.pyplot as plt

# annotations
import textwrap
import math
import re
from matplotlib.ticker import FormatStrFormatter
from highlight_text import fig_text, ax_text
from matplotlib import font_manager
from matplotlib.font_manager import FontProperties

# animation
from PIL import Image, ImageSequence
from matplotlib.animation import FuncAnimation









# url = "https://raw.githubusercontent.com/holtzy/the-python-graph-gallery/master/static/data/global-plastics-production-interpolated.csv"
# url = "https://github.com/TonyFly3000/kaggle/blob/master/global-plastics-production.csv"
df = pd.read_csv("/home/nicolas/Github/Programacion/Python/pandas_plot/global-plastics-production.csv")

#df.reset_index(inplace=True)
# df['year'] = np.linspace(1950, 2050, 1001)
# df.index = df['year']
# df.drop(columns=['year'], inplace=True)
print(df.head())








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

# # Update function for the animation
def update(frame):

    # skip first frame
    if frame == 0:
        return None

    # initialize subset of data
    subset_df = df.iloc[:frame]
    ax.clear()
    ax.yaxis.set_major_formatter(FormatStrFormatter('%.0f'))

    # create the line chart
    ax.plot(subset_df.index, subset_df['plastic-production'], color=line_color)
    ax.scatter(subset_df.index[-1], subset_df['plastic-production'].values[-1], color=line_color, s=100)

# # create and save animation
path = 'web-animated-line-chart-with-text-1.gif'
ani = FuncAnimation(fig, update, frames=len(df))
ani.save(path, fps=5)










# # parameters
# background_color = '#0d1b2a'
# text_color = '#fefae0'
# line_color = '#d90429'
# dpi = 50

# # Setting up the plot
# fig, ax = plt.subplots(figsize=(10, 6), dpi=dpi)
# fig.set_facecolor(background_color)
# ax.set_facecolor(background_color)
# ax.tick_params(axis='y', colors=text_color)
# ax.spines[['left']].set_color(text_color)

# # font
# personal_path = '/Users/josephbarbier/Library/Fonts/'
# font_path = personal_path + 'FiraSans-Light.ttf'
# font = FontProperties(fname=font_path)
# bold_font = FontProperties(fname=personal_path + 'FiraSans-Medium.ttf')

# # Update function for the animation
# def update(frame):

#     # skip first frame
#     if frame == 0:
#         return None

#     # initialize subset of data
#     subset_df = df.iloc[:frame]
#     ax.clear()
#     ax.yaxis.set_major_formatter(FormatStrFormatter('%.0f'))

#     # create the line chart
#     ax.plot(subset_df.index, subset_df['plastic-production'], color=line_color)
#     ax.scatter(subset_df.index[-1], subset_df['plastic-production'].values[-1], color=line_color, s=100)

#     # date in the background
#     year = df.index[frame]
#     fig_text(
#         0.14, 0.3,
#         '1950 - ' + str(round(year)),
#         ha='left', va='top',
#         fontsize=30,
#         font=bold_font,
#         color=text_color,
#         fontweight='bold',
#         alpha=0.3,
#         fig=fig
#     )

#     # custom axes
#     y_min = df.iloc[:frame+1].sum(axis=1).min()
#     y_max = df.iloc[:frame+1].sum(axis=1).max()
#     ax.set_ylim(0, y_max*1.1)
#     ax.spines[['top', 'right', 'bottom']].set_visible(False)
#     ax.set_xticks([])

# # create and save animation
# path = '../../static/animations/web-animated-line-chart-with-text-2.gif'
# ani = FuncAnimation(fig, update, frames=len(df))
# ani.save(path, fps=5)






# # parameters
# background_color = '#0d1b2a'
# text_color = '#fefae0'
# line_color = '#d90429'
# dpi = 50

# # Setting up the plot
# fig, ax = plt.subplots(figsize=(10, 6), dpi=dpi)
# fig.set_facecolor(background_color)
# ax.set_facecolor(background_color)
# ax.tick_params(axis='y', colors=text_color)
# ax.spines[['left']].set_color(text_color)

# # font
# personal_path = '/Users/josephbarbier/Library/Fonts/'
# font_path = personal_path + 'FiraSans-Light.ttf'
# font = FontProperties(fname=font_path)
# bold_font = FontProperties(fname=personal_path + 'FiraSans-Medium.ttf')

# # Update function for the animation
# def update(frame):

#     # skip first frame
#     if frame == 0:
#         return None

#     # initialize subset of data
#     subset_df = df.iloc[:frame]
#     ax.clear()
#     ax.yaxis.set_major_formatter(FormatStrFormatter('%.0f'))

#     # create the line chart
#     ax.plot(subset_df.index, subset_df['plastic-production'], color=line_color)
#     ax.scatter(subset_df.index[-1], subset_df['plastic-production'].values[-1], color=line_color, s=100)

#     # date in the background
#     year = df.index[frame]
#     fig_text(
#         0.14, 0.3,
#         '1950 - ' + str(round(year)),
#         ha='left', va='top',
#         fontsize=30,
#         font=bold_font,
#         color=text_color,
#         fontweight='bold',
#         alpha=0.3,
#         fig=fig
#     )

#     # custom axes
#     y_min = df.iloc[:frame+1].sum(axis=1).min()
#     y_max = df.iloc[:frame+1].sum(axis=1).max()
#     ax.set_ylim(0, y_max*1.1)
#     ax.spines[['top', 'right', 'bottom']].set_visible(False)
#     ax.set_xticks([])

#     # title
#     text = """<Global plastics production has grown dramatically and is set to continue to do so>
#     <Evolution and prediction of annual plastic production>
#     <Data after 2020 are predicted values based on a polynomial regression>
#     """
#     fig_text(
#         0.13, 0.92,
#         text,
#         ha='left', va='top',
#         font=font,
#         highlight_textprops=[
#             {'color':text_color, 'fontsize':14, 'font':bold_font},
#             {'color':text_color, 'fontsize':10},
#             {'color':text_color, 'fontsize':10},
#         ],
#         fig=fig
#     )

#     # credit annotation
#     text = """
#     Developed by <@joseph_barbier>
#     """
#     fig_text(
#         0.9, 0,
#         text,
#         ha='right', va='bottom',
#         fontsize=7, font=font,
#         color=text_color,
#         highlight_textprops=[
#             {'font':bold_font},
#         ],
#         fig=fig
#     )

# # create and save animation
# path = '../../static/animations/web-animated-line-chart-with-text-3.gif'
# ani = FuncAnimation(fig, update, frames=len(df))
# ani.save(path, fps=20)











# def remove_unmatched_lt(text):
#    """
#    Remove unmatched '<' characters from text.

#    Examples:

#    text = '<hello world'
#    remove_unmatched_lt(text)
#    > 'hello world'

#    text = 'hello <world>'
#    remove_unmatched_lt(text)
#    > 'hello <world>'
#    """
#    pattern = r'<(?![^<>]*>)'
#    cleaned_text = re.sub(pattern, '', text)
#    return cleaned_text

# def count_closed_and_enclosed(text):
#    """
#    Count the number of closed and enclosed tags in text.

#    Examples:

#    text = '<hello world>'
#    count_closed_and_enclosed(text)
#    > 1

#    text = '<hello> <world>'
#    count_closed_and_enclosed(text)
#    > 2
#    """
#    closed_pattern = r'<[^<>]*>'
#    closed_tags = re.findall(closed_pattern, text)
#    return len(closed_tags)











# # parameters
# background_color = '#0d1b2a'
# text_color = '#fefae0'
# line_color = '#d90429'
# dpi = 50

# # description
# description = f"""
# During the 1970s, the reputation of plastic was impacted by concerns about unrecycled waste, as plastic <remains in nature forever>. It wasn't until the 1980s that the plastics industry began to <encourage recycling>.

# Around 2007 and 2008, the plastics industry felt the impact of the rise in crude oil prices to the <highest level ever recorded>, due to the credit crunch. 

# If the trend continues, we can expect to exceed the symbolic threshold of <1 billion tons> of plastic produced annually by 2050.
# """

# # Setting up the plot
# fig, ax = plt.subplots(figsize=(10, 6), dpi=dpi)
# fig.set_facecolor(background_color)
# ax.set_facecolor(background_color)
# ax.tick_params(axis='y', colors=text_color)
# ax.spines[['left']].set_color(text_color)

# # font
# personal_path = '/Users/josephbarbier/Library/Fonts/'
# font_path = personal_path + 'FiraSans-Light.ttf'
# font = FontProperties(fname=font_path)
# bold_font = FontProperties(fname=personal_path + 'FiraSans-Medium.ttf')

# # Update function for the animation
# def update(frame):

#     # skip first frame
#     if frame == 0:
#         return None

#     # initialize subset of data
#     subset_df = df.iloc[:frame]
#     ax.clear()
#     ax.yaxis.set_major_formatter(FormatStrFormatter('%.0f'))

#     # create the line chart
#     ax.plot(subset_df.index, subset_df['plastic-production'], color=line_color)
#     ax.scatter(subset_df.index[-1], subset_df['plastic-production'].values[-1], color=line_color, s=100)

#     # date in the background
#     year = df.index[frame]
#     fig_text(
#         0.14, 0.3,
#         '1950 - ' + str(round(year)),
#         ha='left', va='top',
#         fontsize=30,
#         font=bold_font,
#         color=text_color,
#         fontweight='bold',
#         alpha=0.3,
#         fig=fig
#     )

#     # custom axes
#     y_min = df.iloc[:frame+1].sum(axis=1).min()
#     y_max = df.iloc[:frame+1].sum(axis=1).max()
#     ax.set_ylim(0, y_max*1.1)
#     ax.spines[['top', 'right', 'bottom']].set_visible(False)
#     ax.set_xticks([])

#     # title
#     text = """<Global plastics production has grown dramatically and is set to continue to do so>
#     <Evolution and prediction of annual plastic production>
#     <Data after 2020 are predicted values based on a polynomial regression>
#     """
#     fig_text(
#         0.13, 0.92,
#         text,
#         ha='left', va='top',
#         font=font,
#         highlight_textprops=[
#             {'color':text_color, 'fontsize':14, 'font':bold_font},
#             {'color':text_color, 'fontsize':10},
#             {'color':text_color, 'fontsize':10},
#         ],
#         fig=fig
#     )

#     # credit annotation
#     text = """
#     Developed by <@joseph_barbier>
#     """
#     fig_text(
#         0.9, 0,
#         text,
#         ha='right', va='bottom',
#         fontsize=7, font=font,
#         color=text_color,
#         highlight_textprops=[
#             {'font':bold_font},
#         ],
#         fig=fig
#     )

#     # get text to display at current frame
#     total_chars = len(description)
#     effective_frame_count = len(df) - 80 # text ends 80 frames before the video's end
#     num_chars = math.ceil(total_chars * (frame / effective_frame_count)) if frame < effective_frame_count else total_chars
#     current_description = description[:num_chars]
#     current_description = remove_unmatched_lt(current_description) # remove unmatched '<' characters
#     num_closed_tags = count_closed_and_enclosed(current_description) # count number of closed tags
#     if num_closed_tags > 0:
#         highlight_textprops = [{'font':bold_font} for _ in range(num_closed_tags)]
#     else:
#         highlight_textprops = None
#     wrapped_text = '\n'.join([textwrap.fill(paragraph, width=75) for paragraph in current_description.split('\n')])
#     fig_text(
#         0.147, 0.75,
#         wrapped_text,
#         ha='left', va='top',
#         fontsize=10,
#         font=font,
#         color=text_color,
#         highlight_textprops=highlight_textprops,
#         fig=fig
#     )

# # create and save animation
# path = '../../static/animations/web-animated-line-chart-with-text-4.gif'
# ani = FuncAnimation(fig, update, frames=len(df))
# ani.save(path, fps=5)





# def remove_unmatched_lt(text):
#    """
#    Remove unmatched '<' characters from text.

#    Examples:

#    text = '<hello world'
#    remove_unmatched_lt(text)
#    > 'hello world'

#    text = 'hello <world>'
#    remove_unmatched_lt(text)
#    > 'hello <world>'
#    """
#    pattern = r'<(?![^<>]*>)'
#    cleaned_text = re.sub(pattern, '', text)
#    return cleaned_text

# def count_closed_and_enclosed(text):
#    """
#    Count the number of closed and enclosed tags in text.

#    Examples:

#    text = '<hello world>'
#    count_closed_and_enclosed(text)
#    > 1

#    text = '<hello> <world>'
#    count_closed_and_enclosed(text)
#    > 2
#    """
#    closed_pattern = r'<[^<>]*>'
#    closed_tags = re.findall(closed_pattern, text)
#    return len(closed_tags)













# # parameters
# background_color = '#0d1b2a'
# text_color = '#fefae0'
# line_color = '#d90429'
# dpi = 200
# initial_duration = 30

# # font
# personal_path = '/Users/josephbarbier/Library/Fonts/'
# font_path = personal_path + 'FiraSans-Light.ttf'
# font = FontProperties(fname=font_path)
# bold_font = FontProperties(fname=personal_path + 'FiraSans-Medium.ttf')

# # description
# description = f"""
# During the 1970s, the reputation of plastic was impacted by concerns about unrecycled waste, as plastic <remains in nature forever>. It wasn't until the 1980s that the plastics industry began to <encourage recycling>.

# Around 2007 and 2008, the plastics industry felt the impact of the rise in crude oil prices to the <highest level ever recorded>, due to the credit crunch. 

# If the trend continues, we can expect to exceed the symbolic threshold of <1 billion tons> of plastic produced annually by 2050.
# """

# # Setting up the plot
# fig, ax = plt.subplots(figsize=(10, 6), dpi=dpi)
# fig.set_facecolor(background_color)
# ax.set_facecolor(background_color)
# ax.tick_params(axis='y', colors=text_color)
# ax.spines[['left']].set_color(text_color)

# # Update function for the animation
# def update(frame):

#     # skip first frame
#     if frame == 0:
#         return None

#     # initialize subset of data
#     subset_df = df.iloc[:frame]
#     ax.clear()
#     ax.yaxis.set_major_formatter(FormatStrFormatter('%.0f'))

#     # create the line chart
#     ax.plot(subset_df.index, subset_df['plastic-production'], color=line_color)
#     ax.scatter(subset_df.index[-1], subset_df['plastic-production'].values[-1], color=line_color, s=100)

#     # date in the background
#     year = df.index[frame]
#     fig_text(
#         0.14, 0.3,
#         '1950 - ' + str(round(year)),
#         ha='left', va='top',
#         fontsize=30,
#         font=bold_font,
#         color=text_color,
#         fontweight='bold',
#         alpha=0.3,
#         fig=fig
#     )

#     # custom axes
#     y_min = df.iloc[:frame+1].sum(axis=1).min()
#     y_max = df.iloc[:frame+1].sum(axis=1).max()
#     ax.set_ylim(0, y_max*1.1)
#     ax.spines[['top', 'right', 'bottom']].set_visible(False)
#     ax.set_xticks([])

#     # get text to display at current frame
#     total_chars = len(description)
#     effective_frame_count = len(df) - 80 # ends 100 frames before the end
#     num_chars = math.ceil(total_chars * (frame / effective_frame_count)) if frame < effective_frame_count else total_chars
#     current_description = description[:num_chars]
#     current_description = remove_unmatched_lt(current_description)
#     num_closed_tags = count_closed_and_enclosed(current_description)
#     if num_closed_tags > 0:
#         highlight_textprops = [{'font':bold_font} for _ in range(num_closed_tags)]
#     else:
#         highlight_textprops = None
#     wrapped_text = '\n'.join([textwrap.fill(paragraph, width=75) for paragraph in current_description.split('\n')])
#     fig_text(
#         0.147, 0.75,
#         wrapped_text,
#         ha='left', va='top',
#         fontsize=10,
#         font=font,
#         color=text_color,
#         highlight_textprops=highlight_textprops,
#         fig=fig
#     )

#     # title
#     text = """<Global plastics production has grown dramatically and is set to continue to do so>
#     <Evolution and prediction of annual plastic production>
#     <Data after 2020 are predicted values based on a polynomial regression>
#     """
#     fig_text(
#         0.13, 0.92,
#         text,
#         ha='left', va='top',
#         font=font,
#         highlight_textprops=[
#             {'color':text_color, 'fontsize':14, 'font':bold_font},
#             {'color':text_color, 'fontsize':10},
#             {'color':text_color, 'fontsize':10},
#         ],
#         fig=fig
#     )

#     # credit annotation
#     text = """
#     Developed by <@joseph_barbier>
#     """
#     fig_text(
#         0.9, 0,
#         text,
#         ha='right', va='bottom',
#         fontsize=7, font=font,
#         color=text_color,
#         highlight_textprops=[
#             {'font':bold_font},
#         ],
#         fig=fig
#     )

# # create and save animation
# path = '../../static/animations/web-animated-line-chart-with-text-5.gif'
# ani = FuncAnimation(fig, update, frames=len(df))
# ani.save(path, fps=20)
# print('Original animation finished')


# # get initial frames
# with Image.open(path) as img:
#     frames = [frame.copy() for frame in ImageSequence.Iterator(img)]

# # set duration of each frame
# for i, frame in enumerate(frames):
#     frame_duration = initial_duration

#     # stay for last date
#     if i == len(frames) - 1:
#         frame_duration = 10000
#     frame.info['duration'] = frame_duration

# # Save the modified frames as a new GIF
# frames[0].save(path, save_all=True, append_images=frames[1:], loop=0)
# print('Final animation finished!')